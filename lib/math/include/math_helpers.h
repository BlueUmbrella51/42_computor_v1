#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H
#include <type_traits>
#include <iostream>
#include <numeric>
#include <limits>
#include <tuple>
#include <vector>
#include <cmath>
#include <assert.h>
#include <limits.h>

#define ACCURACY 0.00000000001

/* Default implementation of getGcd: if either parameter is floating point, return 1 */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_floating_point<T>{} ||
            std::is_floating_point<U>{}, bool>::type = true
		>
long long 	getGcd(T &a, U &b) { return 1; }

/* getGcd for all combinations of integral types */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
long long	getGcd(T &a, U &b) { return std::gcd(a, b); }

template<typename T, typename U, typename V,
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{} &&
			std::is_integral<V>{}, bool>::type = true
		>
long long	getGcd(T &a, U &b, V &c) {
	long long tmp = std::gcd(a, b);
	return std::gcd(tmp, c);
}

/* Get lcm for making denominators equal */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
long long	getLcm(T &a, U &b) { return std::lcm(a, b); }

/* Factor out GCD when GCD and number are integral */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
void		factorGcd(T &a, U &b) {
	long long gcd = getGcd(a, b);
	if (gcd >= 1) {
		// Factor out a negative 1
		if (a < 0 && b < 0) {
			gcd = -gcd;
		}
		a /= gcd;
		b /= gcd;
	}
}

/* Overflow checks for arithmetic operations */
template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	additionExceedsLimits(T lhs, T rhs) {
	/* Check for over- and underflow */
	if (rhs >= 0) {
		return (lhs > std::numeric_limits<T>::max() - rhs);
	}
	else {
		return (lhs < std::numeric_limits<T>::min() - rhs);
	}
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	subtractionExceedsLimits(T lhs, T rhs) {
	/* Check for over- and underflow */
	if (rhs < 0) {
		return (lhs > std::numeric_limits<T>::max() + rhs);
	}
	else {
		return (lhs < std::numeric_limits<T>::min() + rhs);
	}
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	multiplicationExceedsLimits(T lhs, T rhs) {
	/* Check for over- and underflow */
	if (rhs == 0) return false;
	return ((lhs > 0 && rhs > 0 && (lhs > std::numeric_limits<T>::max() / rhs))
	|| (lhs < 0 && rhs < 0 && (lhs < std::numeric_limits<T>::max() / rhs))
	|| (rhs > 0 && lhs < 0 && (lhs < std::numeric_limits<T>::min() / rhs))
	|| (rhs < 0 && lhs > 0 && (lhs > std::numeric_limits<T>::min() / rhs)));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	divisionExceedsLimits(T lhs, T rhs) {
	return (lhs == std::numeric_limits<T>::min() && rhs == -1);
}

// Returns whole part, numerator and denominator
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
std::tuple<long long, long long, long long>	doubleToRatio(T value, long double accuracy = ACCURACY) {
	if (std::isinf(value)) { 
		throw std::invalid_argument("Decimal to convert to ratio cannot be infinite.");}
	if (std::isnan(value)) { 
		throw std::invalid_argument("Decimal to convert to ratio cannot be nan.");}
	if (accuracy < 0.0 || accuracy > 1.0) { 
		throw std::invalid_argument("Accuracy for conversion to ratio must be between 0 and 1.");}
	if (floor(value) <= LONG_LONG_MIN || floor(value) >= LONG_LONG_MAX) {
		throw std::overflow_error("Whole part of decimal is too large to fit integer type\n");}
	
	int				sign = value >= 0.0 ? 1 : -1;
	value = std::abs(value);
	long long 		int_part = (long long)value;
	value -= int_part;

	// check if decimal part is withing permitted error range from 0.0 or equal to 0.0
	if (value - accuracy < 0.0 || value == 0.0) {
		return std::make_tuple(sign * int_part, 0, 1);
	}
	// check if decimal part is withing permitted error range from 1.0
	if (value - accuracy < 0.0) {
		return std::make_tuple(sign * (int_part + 1), 0, 1);
	}

	std::vector<long long> a = {1, 0};
	std::vector<long long> b = {0, 1};

	long double 		x = value;
	size_t				i = 1;
	do {
		++i;
		x = 1 / (x - floor(x));
		if (multiplicationExceedsLimits((long long)x, a[i - 1])
		|| additionExceedsLimits(a[i - 2], (long long)x * a[i - 1])) {
			throw std::overflow_error("Could not find rational approximation \
of decimal within given precision.");
		}
		long long next_a = a[i - 2] + floor(x) * a[i - 1];
		if (multiplicationExceedsLimits((long long)x, b[i - 1])
		|| additionExceedsLimits(b[i - 2], (long long)x * b[i - 1])) {
			throw std::overflow_error("Could not find rational approximation \
of decimal within given precision.");
		}
		long long next_b = b[i - 2] + floor(x) * b[i - 1];
		a.push_back(next_a);
		b.push_back(next_b);
	}
	while (std::abs(((long double)a[i] / (long double)b[i]) - value) > accuracy);

	if (a[i] == LONG_LONG_MIN && sign == -1){
		throw std::overflow_error("Could not find rational approximation \
of decimal within given precision.");
	}
	long long whole = sign * int_part;
	long long denominator = b[i];
	long long numerator = sign * a[i];
	return	std::make_tuple(whole, numerator, denominator);
}

template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
long long	int_pow(T base, U exp) {
	long long result = 1;

	if (exp < 0) { throw std::invalid_argument("Cannot raise integer to negative power."); }
	if (exp == 0) { return result; }
	if (base == 0) { return 0; }
	while (exp) {
		if (multiplicationExceedsLimits(result, (long long)base)) {
			throw std::overflow_error("Could not perform exponentiation of integer without overflow.");
		}
		result *= base;
		exp--;
	}
	return result;
}

#endif
