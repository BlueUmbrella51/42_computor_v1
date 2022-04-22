cmake_minimum_required(VERSION 3.10)

find_package(Git REQUIRED)

# Configuration options

set(TESTS off CACHE BOOL "Create unit tests or not")

set(catchFolder ${CMAKE_CURRENT_LIST_DIR}/external/catch2)
set(catchFile ${catchFolder}/CMakeLists.txt)

# Imports git submodule
if (NOT EXISTS ${catchFile})
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${catchFolder}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE RES)
	if (NOT RES EQUAL "0")
		message("Could not update catch library!\n")
	endif()
endif()

set(headerDir include)
set(compSourceDir ${CMAKE_CURRENT_LIST_DIR}/computor/)
set(computorHeaderDir ${CMAKE_CURRENT_LIST_DIR}/computor/${headerDir})
set(mathHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/math/${headerDir})
set(polynomialHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/polynomials/${headerDir})
set(numericalHeaderDir ${CMAKE_CURRENT_LIST_DIR}/lib/numerical_classes/${headerDir})

set(mathName math_helpers)
set(numerName numerical_classes)
set(polyName polynomials)

message(${computorHeaderDir})
message(${mathHeaderDir})

project(computor)

add_subdirectory(lib)
add_subdirectory(computor)

IF (${TESTS})
	message("BUILDING TESTS...\n")
	enable_testing()
	list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/external/catch2/contrib)
	set(catchFilePath ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2)
	set(catchHeaderName catch.hpp)
	add_subdirectory(external/catch2)
	add_subdirectory(tests)
endif()

