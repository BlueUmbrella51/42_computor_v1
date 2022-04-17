add_executable(computor 
	computor.cpp
	solver.cpp
)

target_compile_features(computor PUBLIC cxx_std_17)

target_link_libraries(computor
	PRIVATE polynomials
)

target_include_directories(computor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# add_subdirectory(tests)