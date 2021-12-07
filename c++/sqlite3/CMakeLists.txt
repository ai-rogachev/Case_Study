cmake_minimum_required(VERSION 3.5)

project(27.DB)

find_package(Threads)

add_executable(main main.cpp sqlite3.c)

set_target_properties(main PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

IF (UNIX)
target_link_libraries(main
        ${CMAKE_THREAD_LIBS_INIT}
        dl
        )
ENDIF()