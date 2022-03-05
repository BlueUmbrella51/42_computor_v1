add_library(${mathName}
			doubleToRational.cpp
			greatestCommonDivisor.cpp
)

add_subdirectory(tests)

target_include_directories(${mathName} PUBLIC ${headerDir})

target_link_libraries(${mathName} PRIVATE ${numerName})
