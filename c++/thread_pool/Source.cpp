/*
	-- bad concurrency idea;
	Test1 - elapsed time is 1699.18 ms
	Test2 - elapsed time is 1.453 ms

	-- good concurrency idea;
	Test4 - elapsed time is 0.0294 ms
	Test5 - elapsed time is 9.8361 ms
*/

#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>


#include "priority.h"
#include "thread_pool.h"

const size_t NUMBER = 1'000'000;

void Test1()
{
	concur::StaticThreadPool pool{4};	
	std::atomic<size_t> tasks1{ 0 };
	std::atomic<size_t> tasks2{ 0 };
	std::atomic<size_t> tasks3{ 0 };
	std::atomic<size_t> tasks4{ 0 };

	auto t_start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < NUMBER; ++i)
	{
		pool.Submit(
			[&](){
				++tasks1;
				++tasks2;
				++tasks3;
				++tasks4;
			}
		);
	}
	
	// the work...
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "Test1 - elapsed time is " << elapsed_time_ms << " ms" << std::endl;

	pool.Join();

	assert(tasks1.load(), NUMBER);
}


void Test2()
{
	size_t tasks1{ 0 };
	size_t tasks2{ 0 };
	size_t tasks3{ 0 };
	size_t tasks4{ 0 };

	auto t_start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < NUMBER; ++i)
	{
		++tasks1;
		++tasks2;
		++tasks3;
		++tasks4;
	}

	// the work...
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "Test2 - elapsed time is " << elapsed_time_ms << " ms" << std::endl;

	assert(tasks1, NUMBER);
}


void Test4()
{
	concur::StaticThreadPool pool{ 4 };
	std::atomic<size_t> summ{ 0 };
	std::vector<int> arr(NUMBER, 1);

	auto t_start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < NUMBER; i += NUMBER / 5)
	{
		pool.Submit(
			[&summ, &arr, i]() {
				for (int g = i; g < i + NUMBER / 5; ++g)
				{
					summ += arr[g];
				}
			}
		);
	}

	// the work...
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "Test4 - elapsed time is " << elapsed_time_ms << " ms" << std::endl;

	pool.Join();

	assert(summ, NUMBER);
}


void Test5()
{
	std::atomic<size_t> summ{ 0 };
	std::vector<int> arr(NUMBER, 1);

	auto t_start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < NUMBER; ++i)
	{
		summ += arr[i];
	}

	// the work...
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "Test5 - elapsed time is " << elapsed_time_ms << " ms" << std::endl;

	assert(summ, NUMBER);
}

void TestThreadPool()
{
	// harm from concurrency
	std::cout << "-- bad concurrency idea;" << std::endl;
	Test1();
	Test2();

	// denefit from concurrency
	std::cout << "-- good concurrency idea;" << std::endl;
	Test4();
	Test5();
}

void TestPriorityExecutor()
{
	auto pool = concur::MakeStaticPool(4);
	auto prior = concur::MakePriorityExecutor(pool);

	prior->Execute(100, 
		[]() {
			std::cout << "Task priority = 100 / id = " << 
				std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	prior->Execute(0,
		[]() {
			std::cout << "Task priority = 0 / id = " <<
				std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	);

	prior->Execute(200,
		[]() {
			std::cout << "Task priority = 200 / id = " <<
				std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	);

	pool->Join();
}

int main()
{
	//TestThreadPool();
	TestPriorityExecutor();

	std::cin.get();
	return 0;
}