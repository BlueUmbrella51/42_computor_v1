add_executable(computor 
	computor.cpp
	computor.h
	parser.cpp
	solver.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE polynomials
)

target_include_directories(computor 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
