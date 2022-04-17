#ifndef COMPUTOR_H
#define COMPUTOR_H

#include "Equation.h"
#include "Solution.h"

Equation	parse_equation(std::string &equation);
Solution	solve_equation(Equation &e);
#endif
