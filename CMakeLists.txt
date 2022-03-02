cmake_minimum_required(VERSION 3.10)

# set the project name
project(Computor)

# add the executable
add_executable(computor src/computor/computor.cpp)
set_property(TARGET computor PROPERTY CXX_STANDARD 17)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify compiler
set(CMAKE_CXX_COMPILER "clang++")
