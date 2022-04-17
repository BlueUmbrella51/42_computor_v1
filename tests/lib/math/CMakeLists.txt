add_executable(math_tests
	tests.cpp
)

target_compile_features(math_tests PUBLIC cxx_std_17)

target_include_directories(math_tests
	PRIVATE ${numericalHeaderDir}
	PRIVATE ${mathHeaderDir}
	PRIVATE ${catchFilePath}
)

target_link_libraries(math_tests 
	PRIVATE ${numerName}
	PRIVATE Catch2::Catch2
)

include(Catch)
include(CTest)
catch_discover_tests(math_tests)
