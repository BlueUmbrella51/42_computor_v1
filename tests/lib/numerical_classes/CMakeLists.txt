add_executable(rationals_tests
	rationals.cpp
)

target_compile_features( rationals_tests PUBLIC cxx_std_17)

target_include_directories( rationals_tests 
	PRIVATE ${numericalHeaderDir}
	PRIVATE ${catchFilePath}
)

target_link_libraries( rationals_tests 
	PRIVATE ${mathName}
	PRIVATE ${numerName}
	PRIVATE Catch2::Catch2
)

add_executable(roots_tests
	roots.cpp
)

target_compile_features(roots_tests PUBLIC cxx_std_17)

target_include_directories(roots_tests 
	PRIVATE ${mathHeaderDir}
	PRIVATE ${numericalHeaderDir}
	PRIVATE ${catchFilePath}
)

target_link_libraries(roots_tests 
	PRIVATE ${numerName}
	PRIVATE ${mathName}
	PRIVATE Catch2::Catch2
)

include(Catch)
include(CTest)
catch_discover_tests(rationals_tests)
catch_discover_tests(roots_tests)