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

// TODO: limit types
template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
std::optional<T>	abs_overflow(T n) {
	if (n < 0) {
		T prev = n;
		n *= -1;
		if (n * -1 != prev) { return std::nullopt; }
		return n;
	}
	return n;
}

template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
std::optional<T>	integral_pow_overflow(T base, T exp) {
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

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
std::tuple<long long int, long long int>	doubleToRatio(T value, long double accuracy) {
	if (std::isinf(value) || std::isnan(value)) {
		throw std::invalid_argument("Argument to covert cannot be NaN or INF.");
	}
	if (accuracy < 0.0 || accuracy > 1.0) {
		throw std::invalid_argument("Accuracy must be number between 0.0 and 1.0.");
	}
	int	sign = value >= 0.0 ? 1 : -1;
	// TODO: abs value
	long double abs_val = std::abs(value);
	long double dec_part = abs_val - floor(abs_val);

	// Handles integer numbers including 0.0
	if (abs_val == (long long)abs_val) {
		return std::make_tuple(sign * (long long)abs_val, 1);
	}
	std::vector<long long> a = {1, 0};
	std::vector<long long> b = {0, 1};

	long double 		x = 1 / (abs_val - floor(abs_val));
	long double 		z;
	size_t		i = 2;
	long long 	a_term, b_term = 0;
	double chk = 1.0;
	do {
		z = floor(x);
		long long next_a = a[i - 2] + floor(z) * a[i - 1];
		long long next_b = b[i - 2] + floor(z) * b[i - 1];
		if ((floor(z) != 0 && a[i - 1] != (next_a - a[i - 2]) / floor(z))
		|| (b[i - 1] != 0 && b[i - 1] != (next_b - b[i - 2]) / floor(z))) {
			throw std::overflow_error("Could not find rational approximation of value with given accuracy without overflow.");
		}
		a.push_back(a[i - 2] + floor(z) * a[i - 1]);
		b.push_back(b[i - 2] + floor(z) * b[i - 1]);
		a_term = a[i];
		b_term = b[i];
		x = 1 / (x - floor(x));
		chk = abs(((double)a_term / (double)b_term) - dec_part);
		i++;
	}
	while (chk > accuracy);
	// TODO: handle overflow and put "whole" part back in
	long long numerator = sign * (a_term + ((abs_val - dec_part) * b_term));
	if (a_term != sign * (numerator - ((abs_val - dec_part) * b_term))) {
		throw std::overflow_error("Could not find rational approximation of value with given accuracy without overflow.");
	}
	return	std::make_tuple(numerator, b_term);
}



#endif
