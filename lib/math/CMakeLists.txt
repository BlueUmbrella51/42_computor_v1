add_library(${mathName}
			greatestCommonDivisor.cpp
			llFactorGcd.cpp
)

target_compile_features(${mathName} PUBLIC cxx_std_17)

add_subdirectory(tests)

target_include_directories(${mathName} PUBLIC ${headerDir})
