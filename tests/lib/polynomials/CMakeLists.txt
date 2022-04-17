add_executable(parsing_tests
	parser.cpp
)

target_compile_features(parsing_tests PUBLIC cxx_std_17)

target_include_directories(parsing_tests 
	PRIVATE ${polynomialHeaderDir}
	PRIVATE ${catchFilePath}
)

target_link_libraries(parsing_tests 
	PRIVATE ${polyName}
	PRIVATE Catch2::Catch2
)

include(Catch)
include(CTest)
catch_discover_tests(parsing_tests)