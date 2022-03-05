add_library(${polyName} STATIC
	Equation.cpp
	Token.cpp	
)

target_include_directories(${polyName} PUBLIC ${headerDir})

target_link_libraries(${polyName} 
	${numerName}
	${mathName}
)
