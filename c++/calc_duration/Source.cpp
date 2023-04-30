#include <iostream>
#include <thread>

#include "utils.h"

void test()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
}

size_t test2(int a, int b)
{
	size_t result = static_cast<size_t>(a) + b;
	return result;
}

int main()
{
	perf_timer<> timer;
	timer.start();

	// check duration timer
	auto time = perf_timer<>::duration(test);
	std::chrono::milliseconds ms_time = 
		std::chrono::duration_cast<std::chrono::milliseconds>(time);

	std::cout << ms_time.count() << std::endl;
	time = perf_timer<>::duration(test2, 10, 20);
	std::cout << time.count() << std::endl;

	// check total time
	ms_time =
		std::chrono::duration_cast<std::chrono::milliseconds>(timer.end());
	std::cout << ms_time.count() << std::endl;;

	// check time by start/stop
	timer.start();
	test();
	ms_time =
		std::chrono::duration_cast<std::chrono::milliseconds>(timer.end());
	std::cout << ms_time.count() << std::endl;

	return 0;
}