add_library(math_helpers STATIC
			math_helpers.h
			doubleToRational.cpp
			greatestCommonDivisor.cpp
)

target_link_libraries(math_helpers PRIVATE numerical_classes)

target_include_directories(math_helpers 
	PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
