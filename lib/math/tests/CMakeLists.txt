add_executable(math_tests
	tests.cpp
)

message("CATCH FILE PATH ${catchFilePath}")

target_include_directories(math_tests 
	PRIVATE ../${headerDir}
	PRIVATE ${catchFilePath}
)

target_link_libraries(math_tests PRIVATE ${numerName})
target_link_libraries(math_tests PRIVATE Catch2::Catch2WithMain)
