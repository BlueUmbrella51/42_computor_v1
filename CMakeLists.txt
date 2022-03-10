cmake_minimum_required(VERSION 3.10)


# set(CXX_STANDARD 17)
# set(CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic -g")
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

# include(CTest)
# include(Catch)
# Download catch2 header if not present yet
# if (NOT EXISTS ${catchFilePath}/${catchHeaderName})
#     file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.13.8/catch.hpp external/catch2/catch.hpp)
# endif()

add_subdirectory(external/catch2)
add_subdirectory(lib)
add_subdirectory(computor)

# target_link_libraries(foo PRIVATE Catch2::Catch2)
# include(${catchFilePath}/${catchHeaderName})

# add_library(Catch INTERFACE)
# message("CATCH FILE PATH ${catchFilePath}/${catchHeaderName}")
# target_include_directories(Catch INTERFACE ${catchFilePath})

#https://github.com/catchorg/Catch2/releases/download/v2.13.8/catch.hpp

# add_dependencies(computor Run_math_tests)
