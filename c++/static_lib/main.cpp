#include <iostream>
#include "lib\mylib.h"

int main()
{
    std::cout << add(5, 5) << std::endl;
    std::cout << sub(10, 5) << std::endl;

    std::cin.get();
    return EXIT_SUCCESS;
}