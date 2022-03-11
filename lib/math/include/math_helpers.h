#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <math.h>
#include <cmath>
#include <vector>
#include <tuple>
#include <optional>
#include <functional>
#include <numeric>
#include <limits.h>

#define ACCURACY 0.00000000001

class Rational;

// long int		gcd(long int a, long int b);
// Rational        doubleToRational(double num, double accuracy = ACCURACY);
std::tuple<long long int, long long int>   	doubleToRatio(long double num, long double accuracy = ACCURACY);
void			ll_factor_gcd(long long *num, long long *denum);
long long		getGcd(long double lhs, long double rhs);
long long		getGcd(long double lhs, long long rhs);
long long		getGcd(long long lhs, long double rhs);
long long 		getGcd(long long lhs, long long rhs);

template <typename T>
std::optional<T>	abs_overflow(T n) {
	if (n < 0) {
		T prev = n;
		n = llabs(n);
		if (n * -1 != prev) { return std::nullopt; }
		return n;
	}
	return n;
}
template <typename T>
std::optional<T>	pow_overflow(T base, int exp) {
	T	result = 1;
	T	prev = 0;
	T	tmp = 0;

	if (exp < 0) { return std::nullopt; }
	if (exp == 0) { return result; }
	if (base == 0) { return 0; }
    for (;;)
    {
        if (exp & 1) {
			prev = result;
            result *= base;
			if (result / base != prev) { return std::nullopt; }
		}
        exp >>= 1;
        if (!exp)
            break;
		prev = base;
		tmp = base * base;
		if (tmp / base != prev) { return std::nullopt; }
		base = tmp;
    }
    return result;
}
#endif
