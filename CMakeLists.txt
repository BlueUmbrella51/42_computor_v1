cmake_minimum_required(VERSION 3.10)

# set the project name
project(computor)

# add the executable
add_executable(${PROJECT_NAME} 
        src/computor.cpp 
        src/parser.cpp 
        src/solver.cpp)

# specify the C++ standard
set_target_properties(computor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# # specify compiler
# set(CMAKE_CXX_COMPILER "clang++")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
option(USE_CLANG "build application with clang" ON)

# add other directories to check for CMakeLists files
add_subdirectory(src/classes)
add_subdirectory(src/math)

include_directories(src/headers src/classes/headers src/math/headers)

# target_include_directories(src/headers)
target_link_libraries (computor LINK_PUBLIC numerical_classes math_helpers)
