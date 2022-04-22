cmake_minimum_required(VERSION 3.10)

add_library(${numerName} STATIC
			Fraction.cpp
			Rational.cpp
			SquareRoot.cpp
			Numerical.cpp
)

target_compile_features(${numerName} PUBLIC cxx_std_17)

target_include_directories(${numerName} 
	PUBLIC ${headerDir}
	PUBLIC ${mathHeaderDir})

target_link_libraries(${numerName} PRIVATE ${mathName})
