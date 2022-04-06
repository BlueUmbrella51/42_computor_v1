set(mathName math_helpers)
set(numerName numerical_classes)
set(polyName polynomials)

set(headerDir include)

set(mathHeaderDir ${CMAKE_CURRENT_LIST_DIR}/math/${headerDir})
set(polynomialHeaderDir ${CMAKE_CURRENT_LIST_DIR}/polynomial/${headerDir})
set(numericalHeaderDir ${CMAKE_CURRENT_LIST_DIR}/numerical_classes/${headerDir})

add_subdirectory(math)
add_subdirectory(numerical_classes)
add_subdirectory(polynomials)

add_subdirectory(tests)
