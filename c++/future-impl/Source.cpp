#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

#include "promise.h"

int main()
{
	auto [f, p] = future_impl::MakeContract<int>();

	std::thread thread(
		[p = std::move(p)]() mutable {
			std::cout << std::this_thread::get_id() 
				<< " Start to sleep 2s" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << std::this_thread::get_id() 
				<< " End to sleep and set value" << std::endl;
			std::move(p).SetValue(42);
		}
	);
	while (!f.IsReady())
	{
		std::cout << std::this_thread::get_id()
			<< " Wait value from other thread" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << std::this_thread::get_id() << " "
		<< std::move(f).GetValue();
	thread.join();

	std::cin.get();
	return 0;
}