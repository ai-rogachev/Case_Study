#pragma once

#include <iostream>
#include <string>


void DebugLog(std::string&& str) {
#ifdef SERVICE
    std::cout << str << std::endl;
#endif // !SERVICE
}

void DebugLog(int value) {
    std::cout << value << std::endl;
}

void DebugLog(double value) {
    std::cout << value << std::endl;
}

void DebugLog(std::string str, bool val) {
#ifdef SERVICE
    std::cout << str << val << std::endl;
#endif // !SERVICE
}

void DebugLog(std::string str1, int val, std::string str2, int val2) {
#ifdef SERVICE
    std::cout << str1 << val << str2 << val2 << std::endl;
#endif // !SERVICE
}