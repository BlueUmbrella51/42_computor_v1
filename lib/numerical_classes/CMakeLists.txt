cmake_minimum_required(VERSION 3.10)

add_library(${numerName} STATIC
			Complex.cpp
			Rational.cpp
)

target_include_directories(${numerName} PUBLIC ${headerDir})

target_link_libraries(${numerName} PRIVATE ${mathName})
