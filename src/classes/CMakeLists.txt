add_library(numerical_classes 
			Complex.cpp
			Equation.cpp
			Rational.cpp
			Token.cpp
)

include_directories(headers ../math/headers)
# target_include_directories(numerical_classes 
# 	PUBLIC headers
# 	PUBLIC ../math/headers
# )
set_target_properties(numerical_classes PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)