#ifndef COMPUTOR_H
#define COMPUTOR_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "../../classes/headers/Rational.hpp"
#include "../../math/headers/math_helpers.hpp"
#include "../../classes/headers/Equation.hpp"

Equation	parse_equation(std::string &equation);
#endif
