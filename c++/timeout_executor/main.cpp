#include <iostream>
#include <chrono>
#include "TimeoutExecutor.h"
#include <future>


int main()
{
    using namespace std::chrono_literals;
    concur::TimeoutExecutor executor;
    //std::vector<int> delay{10, 20, 30, 40, 500, 600, 70};
    std::vector<int> delay{10, 20, 30, 40, 50, 6, 70};

    for (auto& i : delay)
    {
        executor.Execute([i]() {
            std::this_thread::sleep_for(i * 1ms);
            std::cout << i << std::endl;
        });
    }

    if (executor.WaitFor(100ms))
        std::cout << "Complited" << std::endl;
    else
        std::cout << "Time out" << std::endl;

    return 0;
}