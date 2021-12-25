cmake_minimum_required(VERSION 3.8)
project(WinHooks VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_GENERATOR_PLATFORM win32)

set(This WinHooks)

set(Sources
    HookLoader.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Applications
)

target_include_directories(${This} PUBLIC include)

# app.exe and foo.dll will be in bin subfolder of build dir 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# suppose that the target named `app`,
# i.e. it is added by add_executable(app .....)  

add_subdirectory(lib)

target_link_libraries(${This} WinHooksLib)