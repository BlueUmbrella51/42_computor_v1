cmake_minimum_required(VERSION 3.10)

# add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_library(numerical_classes STATIC
			Complex.cpp
			Complex.h
			Rational.cpp
			Rational.h
)

target_link_libraries(numerical_classes PRIVATE math_helpers)

target_include_directories(numerical_classes 
	PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
