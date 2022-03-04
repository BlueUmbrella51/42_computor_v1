add_library(polynomials STATIC
	Equation.h
	Equation.cpp
	Token.h
	Token.cpp	
)

target_include_directories(polynomials 
	PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  

)

target_link_libraries(polynomials 
	numerical_classes
	math_helpers
)
