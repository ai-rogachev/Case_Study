// JumpTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Jump.h"

int main()
{
    JumpContext ctx;

    size_t jump_count = 0;
    static const size_t kJumpsNeeded = 10;

    Capture(&ctx);
    ++jump_count;

    if (jump_count < kJumpsNeeded) {
        JumpTo(&ctx);  // Jump to Capture(&ctx)
        // JumpTo does not return
        std::cout << "JumpTo returns control";
    }

    std::cin.get();
    return 0;
}