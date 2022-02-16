cmake_minimum_required(VERSION 3.10)
project(lisp-interpreter)

# Set C++17 standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Set release flags, should add debug in the future
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Add all libraries to the include path
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/src" )

# Include GTest testing framework
include(CTest)
include(GoogleTest)
find_package(GTest REQUIRED CONFIG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/src" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/run" )
