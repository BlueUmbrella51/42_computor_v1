#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <math.h>
#include <cmath>
#include "Rational.h"
#define ACCURACY 0.000000001

class Rational;

long int		gcd(long int a, long int b);
Rational        doubleToRational(double num, double accuracy = ACCURACY);

#endif
