cmake_minimum_required(VERSION 3.2)

set(This TutorialAsm8)
project(${This} VERSION 1.0.0)

ENABLE_LANGUAGE(ASM_MASM)

file(GLOB SOURCECS
	*.asm
    *.cpp
    )
	
# создать выходной файл EXE
add_executable(${This} ${SOURCECS})

set_target_properties(${This} 
    PROPERTIES FOLDER Applications
    )

set_source_files_properties(
    *.asm
    PROPERTIES
    COMPILE_FLAGS "/safeseh"
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties(${This} PROPERTIES COMPILE_OPTIONS -W3)
else()
    set_target_properties(${This} PROPERTIES COMPILE_OPTIONS -Wpedantic -Wall -Wextra)
endif()