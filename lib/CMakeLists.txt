# set(mathName math_helpers)
# set(numerName numerical_classes)
# set(polyName polynomials)

# set(mathHeaderDir ${CMAKE_CURRENT_LIST_DIR}/math/${headerDir})
# set(polynomialHeaderDir ${CMAKE_CURRENT_LIST_DIR}/polynomials/${headerDir})
# set(numericalHeaderDir ${CMAKE_CURRENT_LIST_DIR}/numerical_classes/${headerDir})

add_subdirectory(math)
add_subdirectory(numerical_classes)
add_subdirectory(polynomials)

