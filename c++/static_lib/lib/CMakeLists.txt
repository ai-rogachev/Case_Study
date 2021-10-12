cmake_minimum_required(VERSION 3.8)
set(This lib)

set(Headers
    mylib.h
)

set(Sources
    mylib.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

add_compile_definitions(MYLILB_EXPORT)