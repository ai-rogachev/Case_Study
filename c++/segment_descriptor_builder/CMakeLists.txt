cmake_minimum_required(VERSION 3.2)

set(This TutorialCppSegmentDescriptorBuilder)
project(${This} VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCECS
	*.h
    *.cpp
    )
	
# создать выходной файл EXE
add_executable(${This} ${SOURCECS})

set_target_properties(${This} 
    PROPERTIES FOLDER Applications
    )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties(${This} PROPERTIES COMPILE_OPTIONS -W3)
else()
    set_target_properties(${This} PROPERTIES COMPILE_OPTIONS -Wpedantic -Wall -Wextra)
endif()