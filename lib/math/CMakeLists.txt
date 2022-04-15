add_library(${mathName} STATIC
	math_helpers.cpp	
)

target_compile_features(${mathName} PUBLIC cxx_std_17)

target_include_directories(${mathName} PUBLIC ${headerDir})
