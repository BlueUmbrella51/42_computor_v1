cmake_minimum_required(VERSION 3.10)


# set(CXX_STANDARD 17)
# set(CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic -Wno-unused-parameter -g")
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)
# # set(CXX_FLAGS "-std=c++17")
# # set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED OFF)
# set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/external/catch2/contrib)
set(catchFilePath ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2)
set(catchHeaderName catch.hpp)

project(computor)

add_subdirectory(external/catch2)
add_subdirectory(lib)
add_subdirectory(computor)

