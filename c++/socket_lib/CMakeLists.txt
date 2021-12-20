set(This socket_lib)

# Either specify BOOST_ROOT or BOOST_INCLUDEDIR and BOOST_LIBRARYDIR.
# I am using "MinGW Distro" in this example, but also a relative path, e. g.
# "vendor/boost" can be specified.
set (BOOST_ROOT "e:/030 Libs c++/boost_1_75_0/")
set (BOOST_LIBDIR "E:/030 Libs c++/boost_1_75_0/stage/lib")

#set (BOOST_INCLUDEDIR "C:/MinGW/include")
#set (BOOST_LIBRARYDIR "C:/MinGW/lib")
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

# Load settings for the external project "Boost".
# The components "system" and "filesystem" from "Boost" version 1.55.0 or
# greater are required.
find_package (Boost 1.75.0 REQUIRED COMPONENTS system thread)
if (Boost_FOUND)
  # From the offical documentation:
  # Add include directories to the build. [...] If the SYSTEM option is given,
  # the compiler will be told the directories are meant as system include
  # directories on some platforms (signalling this setting might achieve effects
  # such as the compiler skipping warnings [...])."
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})

  # From the offical documentation:
  # "Specify directories in which the linker will look for libraries. [...] Note
  # that this command is rarely necessary. Library locations returned by
  # find_package() and find_library() are absolute paths. Pass these absolute
  # library file paths directly to the target_link_libraries() command. CMake
  # will ensure the linker finds them."
  #link_directories (${Boost_LIBRARY_DIRS})
endif ()

SET(USED_LIBS 
        ${Boost_SYSTEM_LIBRARY} 
        ${Boost_REGEX_LIBRARY}
        ${Boost_LIBRARIES}
    )

set(Sources
    include/ServerSocket.h
	source/ServerSocket.cpp
)
if(MSVC)
    list(APPEND Sources
    )
else()
    list(APPEND Sources
    )
endif()

add_definitions(-DBOOST_ALL_NO_LIB)

add_compile_definitions(_WIN32_WINNT=0x0601)

add_library(${This} ${Sources})
set_target_properties(${This} PROPERTIES FOLDER Libraries)
target_include_directories(${This} PUBLIC include)

TARGET_LINK_LIBRARIES(${This} ${USED_LIBS})