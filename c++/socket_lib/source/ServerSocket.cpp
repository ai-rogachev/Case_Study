//------------------------------------------------------------------------------
//
// WebSocket server, asynchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include "ServerSocket.h"
#include <iostream>

namespace Sockets
{
	namespace beast = boost::beast;         // from <boost/beast.hpp>
	namespace http = beast::http;           // from <boost/beast/http.hpp>
	namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
	namespace net = boost::asio;            // from <boost/asio.hpp>
	using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

	//---------------------------------------------------
	// Report a failure
	void fail(beast::error_code ec, char const* what)
	{
		std::cerr << what << ": " << ec.message() << "\n";
	}

	struct ServerClientImpl : public ServerSocket::Client, 
			public std::enable_shared_from_this<ServerClientImpl>
	{
		Sockets::ServerSocket::OnReceived m_onReceived;
		Sockets::ServerSocket::OnClosed m_onClose;

		websocket::stream<beast::tcp_stream> m_ws;
		std::vector<boost::shared_ptr<std::string const>> m_queue;
		beast::flat_buffer m_buffer;

	public:
		explicit ServerClientImpl(tcp::socket&& socket)
			: m_ws(std::move(socket))
		{
		}
		
		// Inherited via Client
		virtual void Close() override
		{
			m_onClose();
		}

		virtual void Start(
			Sockets::ServerSocket::OnReceived onReceived,
			Sockets::ServerSocket::OnClosed onClose) override
		{
			m_onReceived = onReceived;
			m_onClose = onClose;

			net::dispatch(
				m_ws.get_executor(),
				beast::bind_front_handler(
					&ServerClientImpl::OnStart,
					shared_from_this()
				)
			);
		}

		virtual void SendResponse(const std::string& message)
		{
			if (!m_ws.is_open())
			{
				m_onClose();
				return;
			}

			// Put the message in a shared pointer so 
			// we can re-use it for each client
			auto const ss = boost::make_shared<std::string const>
				(std::move(message));

			net::post(
				m_ws.get_executor(),
				beast::bind_front_handler(
					&ServerClientImpl::OnSend,
					shared_from_this(),
					ss
				)
			);
		}

	private:
		void OnStart()
		{
			m_ws.set_option(
				websocket::stream_base::timeout::suggested(
					beast::role_type::server
				)
			);

			m_ws.set_option(
				websocket::stream_base::decorator(
					[](websocket::response_type& res)
					{
						res.set(http::field::server,
							std::string(BOOST_BEAST_VERSION_STRING) +
							" websocket-server-async"
						);
					}
				)
			);

			// Accept the websocket handshake
			m_ws.async_accept(
				beast::bind_front_handler(
					&ServerClientImpl::OnAccept,
					shared_from_this()
				)
			);
		}

		void OnAccept(beast::error_code ec)
		{
			if (ec)
				return fail(ec, "accept client");

			DoRead();
		}

		void DoRead()
		{
			m_ws.async_read(
				m_buffer,
				beast::bind_front_handler(
					&ServerClientImpl::OnRead,
					shared_from_this()
				)
			);
		}

		void OnRead(
			beast::error_code ec,
			std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);

			if (ec == websocket::error::closed)
			{
				Close();
				return;
			}

			if (ec)
				fail(ec, "read");

			// Call OnReceived from client side
			std::string msg;
			msg = beast::buffers_to_string(m_buffer.data());
			m_onReceived(msg);

			// Clear the buffer
			m_buffer.consume(m_buffer.size());

			// Read another message
			m_ws.async_read(
				m_buffer,
				beast::bind_front_handler(
					&ServerClientImpl::OnRead,
					shared_from_this()
				)
			);
		}

		void OnSend(boost::shared_ptr<std::string const> const& ss)
		{
			// Always add to queue
			m_queue.push_back(ss);

			// Are we already writing?
			if (m_queue.size() > 1)
				return;

			// We are not currently writing, so send this immediately
			m_ws.async_write(
				net::buffer(*m_queue.front()),
				beast::bind_front_handler(
					&ServerClientImpl::OnWrite,
					shared_from_this()));
		}

		void OnWrite(
			beast::error_code ec,
			std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);

			// Handle the error, if any
			if (ec)
				return fail(ec, "write");

			// Remove the string from the queue
			m_queue.erase(m_queue.begin());

			// Send the next message if any
			if (!m_queue.empty())
				m_ws.async_write(
					net::buffer(*m_queue.front()),
					beast::bind_front_handler(
						&ServerClientImpl::OnWrite,
						shared_from_this()));
		}
	};

	//---------------------------------------------------
	class Listener : public std::enable_shared_from_this<Listener>
	{
		Sockets::ServerSocket::OnAcceptClient m_onAcceptClient;

		net::io_context& m_ioc;
		tcp::acceptor m_acceptor;

	public:
		Listener(
			net::io_context& ioc,
			tcp::endpoint endpoint,
			Sockets::ServerSocket::OnAcceptClient onAccept
		) : m_ioc(ioc)
			, m_acceptor(ioc)
			, m_onAcceptClient(onAccept)
		{
			beast::error_code erCode;
			m_acceptor.open(endpoint.protocol(), erCode);
			if (erCode)
			{
				fail(erCode, "open");
				return;
			}

			m_acceptor.set_option(
				net::socket_base::reuse_address(true), erCode
			);
			if (erCode)
			{
				fail(erCode, "set_option");
				return;
			}

			m_acceptor.bind(endpoint, erCode);
			if (erCode)
			{
				fail(erCode, "bind");
				return;
			}

			m_acceptor.listen(
				net::socket_base::max_listen_connections, erCode
			);
			if (erCode)
			{
				fail(erCode, "listen");
				return;
			}
		}

		// ������ ��������� �������� ����������
		void Run()
		{
			DoAccept();
		}

	private:
		void DoAccept()
		{
			m_acceptor.async_accept(
				net::make_strand(m_ioc),
				beast::bind_front_handler(
					&Listener::on_accept,
					shared_from_this()
				)
			);
		}

		void on_accept(
			beast::error_code ec
			, tcp::socket socket)
		{
			if (ec)
			{
				fail(ec, "accept");
			}
			else
			{
				auto client = std::make_shared<ServerClientImpl>(std::move(socket));
				m_onAcceptClient(client);
			}
			DoAccept();
		}
	};
	
	//---------------------------------------------------

	struct ServerSocket::Impl
	{
		std::shared_ptr<Listener> m_listener;
		std::vector<std::thread> m_threads;
		uint16_t m_port;
		std::string m_ip;
		// The io_context is required for all I/O
		std::shared_ptr<net::io_context> m_ioc;
	};


	ServerSocket::ServerSocket() : m_impl(new Impl())
	{
	}

	bool ServerSocket::Bing(const std::string& address, uint16_t port)
	{
		m_impl->m_ip = address;
		m_impl->m_port = port;
		return true;
	}

	bool ServerSocket::Listen(OnAcceptClient onAcceptClient)
	{
		auto const address = net::ip::make_address(m_impl->m_ip);
		auto threads = std::thread::hardware_concurrency();
		if (threads == 0)
			threads = 2;

		m_impl->m_ioc = std::make_shared<net::io_context>(threads);
		// Create and launch a listening port
		m_impl->m_listener = std::make_shared<Listener>(
			*m_impl->m_ioc,
			tcp::endpoint{ address, m_impl->m_port },
			onAcceptClient);

		m_impl->m_listener->Run();

		// Run the I/O service on the requested number of threads
		m_impl->m_threads.reserve(threads-1);
		for (auto i = threads - 1; i > 0; --i)
			m_impl->m_threads.emplace_back(
				[&] {
					m_impl->m_ioc->run();
				}
		);
		
		return true;
	}

	void ServerSocket::Stop()
	{
		m_impl->m_ioc->stop();
		while (!m_impl->m_ioc->stopped())
		{
			std::this_thread::yield();
		}
		for (auto& thread : m_impl->m_threads) {
			if (thread.joinable())
				thread.join();
		}
	}
}