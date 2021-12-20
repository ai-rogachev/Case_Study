#pragma once

#include <functional>
#include <memory>
#include <string>

namespace Sockets
{
	/// <summary>
	/// Server socket.
	/// </summary>
	class ServerSocket
	{
	public:
		class Client;

		/// <summary>
		/// Delegate tyoe for receive messages.
		/// </summary>
		using OnReceived = std::function<void(const std::string&)>;
		/// <summary>
		/// Delegate type for close client connection.
		/// </summary>
		using OnClosed = std::function<void()>;
		/// <summary>
		/// Delegate type for accept new client connection.
		/// </summary>
		using OnAcceptClient = std::function<void(std::shared_ptr<Client>&& client)>;
		/// <summary>
		/// Client on server side.
		/// </summary>
		class Client
		{
		public:
			/// <summary>
			/// Close client connection from 
			/// server side.
			/// </summary>
			virtual void Close() = 0;
			/// <summary>
			/// Send message to the client.
			/// </summary>
			/// <param name="message"></param>
			virtual void SendResponse(const std::string& message) = 0;
			virtual void Start(
				OnReceived onReceived,
				OnClosed onClose
			) = 0;
		};
		/// <summary>
		/// Ctor
		/// </summary>
		ServerSocket();
		/// <summary>
		/// Associate program with port.
		/// </summary>
		/// <param name="port">Port number.</param>
		/// <returns></returns>
		bool Bing(const std::string& address, uint16_t port = 0);
		bool Listen(OnAcceptClient onAcceptClient);

		/// <summary>
		/// Stop server.
		/// </summary>
		void Stop();

	private:
		struct Impl;
		std::shared_ptr<Impl> m_impl;
	};
}