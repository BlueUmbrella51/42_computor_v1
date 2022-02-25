#ifndef MATH_HELPERS_HPP
#define MATH_HELPERS_HPP
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <math.h>
#include <cmath>
#include "../../classes/headers/Rational.hpp"
#define ACCURACY 0.0000001

long int		gcd(long int a, long int b);
Rational        doubleToRational(double num, double accuracy = ACCURACY);

#endif

