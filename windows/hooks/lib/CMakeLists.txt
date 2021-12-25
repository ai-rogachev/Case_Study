cmake_minimum_required(VERSION 3.8)
set(This WinHooksLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_GENERATOR_PLATFORM win32)

set(Headers
    HookLib.h
)

set(Sources
    HookLib.cpp
)

add_library(${This} SHARED ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)