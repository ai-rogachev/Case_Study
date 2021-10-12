cmake_minimum_required(VERSION 3.8)
project(StaticLibTest VERSION 0.1.0 LANGUAGES C CXX)

set(This StaticLibTest)

set(Sources
    main.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Applications
)

target_include_directories(${This} PUBLIC include)
target_link_libraries(${This} lib)

add_subdirectory(lib)