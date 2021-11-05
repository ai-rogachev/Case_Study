cmake_minimum_required(VERSION 3.8)
project(PlugInTest VERSION 0.1.0 LANGUAGES C CXX)

set(This PlugInTest)

set(Sources
    main.cpp
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