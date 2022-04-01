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

include(Catch)
include(CTest)
catch_discover_tests(rationals_tests)