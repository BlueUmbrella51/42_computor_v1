#ifndef TYPES_H
#define TYPES_H

#include <variant>
#include <type_traits>
#include "Rational.h"

typedef	std::variant<float, double, long double> decimal;
typedef	std::variant<int, long, long long>	integral;

typedef	std::variant<decimal, integral, Rational>

#endif