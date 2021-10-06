set(This demo_lib)

set(Sources
    *.h
	*.cpp
)

add_library(${This} ${Sources})
set_target_properties(${This} PROPERTIES FOLDER Libraries)
target_include_directories(${This} PUBLIC include)