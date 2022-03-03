#ifndef COMPUTOR_H
#define COMPUTOR_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "Rational.h"
#include "math_helpers.h"
#include "Equation.h"

Equation	parse_equation(std::string &equation);
void		solve_equation(Equation &e);
#endif
