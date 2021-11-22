#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>

int main()
{
	std::promise<int> promis;
	auto future = promis.get_future();

	std::thread thread([&promis]() {
		std::cout << "set value in " << std::this_thread::get_id() << std::endl;
		promis.set_value(42);
		}
	);
	thread.detach();

	std::cout << "wait a second... in " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "get value : " << future.get() << " in " << std::this_thread::get_id() << std::endl;

	std::cin.get();
	return 0;
}