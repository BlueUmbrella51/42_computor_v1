cmake_minimum_required(VERSION 3.10)

add_library(${numerName} STATIC
			Fraction.cpp
			Rational.cpp
			SquareRoot.cpp
			Numerical.cpp
)

target_include_directories(${numerName} PUBLIC ${headerDir})

target_link_libraries(${numerName} PRIVATE ${mathName})
