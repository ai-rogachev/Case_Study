// AtomicTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "atomics.h"

int main()
{
    AtomicInt64 test = 0;

    auto prev =  AtomicExchange(&test, 7);

    std::cout << "Previous value = " << prev << std::endl;
    std::cout << "Current value = " << test << std::endl;

    std::cin.get();
    return 0;
}