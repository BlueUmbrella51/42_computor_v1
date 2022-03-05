cmake_minimum_required(VERSION 3.10)

project(computor)

set(catchFilePath ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2)
set(catchHeaderName catch.hpp)

# Download catch2 header if not present yet
# if (NOT EXISTS ${catchFilePath}/${catchHeaderName})
#     file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.13.8/catch.hpp external/catch2/catch.hpp)
# endif()

add_subdirectory(external/catch2)
add_subdirectory(lib)
add_subdirectory(computor)

# include(${catchFilePath}/${catchHeaderName})

# add_library(Catch INTERFACE)
# message("CATCH FILE PATH ${catchFilePath}/${catchHeaderName}")
# target_include_directories(Catch INTERFACE ${catchFilePath})

# include(CTest)
# include(Catch)
# catch_discover_tests(MyLibTests)

#https://github.com/catchorg/Catch2/releases/download/v2.13.8/catch.hpp