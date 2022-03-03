add_library(math_helpers 
			doubleToRational.cpp
			greatestCommonDivisor.cpp
)

include_directories(headers ../classes/headers)
# target_include_directories(math_helpers 
# 	PUBLIC headers
# 	PUBLIC ../classes/headers
# )
set_target_properties(math_helpers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)