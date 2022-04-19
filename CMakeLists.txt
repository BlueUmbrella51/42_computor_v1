cmake_minimum_required(VERSION 3.10)

# set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic -Wno-unused-parameter -g")
set(CMAKE_CXX_FLAGS "-g")
find_package(Git REQUIRED)

if (NOT EXISTS external/catch2/CMakeLists.txt)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- external/catch2
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endif()

set(headerDir include)
set(compSourceDir ${CMAKE_CURRENT_LIST_DIR}/computor/)
set(computorHeaderDir ${CMAKE_CURRENT_LIST_DIR}/computor/${headerDir})
set(mathHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/math/${headerDir})
set(polynomialHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/polynomial/${headerDir})
set(numericalHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/numerical_classes/${headerDir})

set(mathName math_helpers)
set(numerName numerical_classes)
set(polyName polynomials)

message(${computorHeaderDir})
message(${mathHeaderDir})
# find_package(Git QUIET)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# # Update submodules as needed
#     option(GIT_SUBMODULE "Check submodules during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update")
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                         RESULT_VARIABLE GIT_SUBMOD_RESULT)
#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#         endif()
#     endif()
# endif()

# if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
#     message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
# endif()

# if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
#     message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
# endif()

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/external/catch2/contrib)
set(catchFilePath ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2)
set(catchHeaderName catch.hpp)

project(computor)

add_subdirectory(external/catch2)
add_subdirectory(lib)
add_subdirectory(computor)

add_subdirectory(tests)

