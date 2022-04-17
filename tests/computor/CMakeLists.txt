add_executable(solution_tests
	solutions.cpp
)

target_compile_features(solution_tests PUBLIC cxx_std_17)

target_include_directories(solution_tests
	PRIVATE ${catchFilePath}
	PRIVATE ${computorHeaderDir}
)

target_link_libraries(solution_tests
	PRIVATE polynomials
)

include(Catch)
include(CTest)
catch_discover_tests(solution_tests)