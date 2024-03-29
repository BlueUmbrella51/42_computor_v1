#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H
#include <type_traits>
#include <iostream>
#include <numeric>
#include <limits>
#include <tuple>
#include <vector>
#include <cmath>
#include <limits.h>
#include <cfenv>
#include <stdexcept>

#define ACCURACY 0.00000000001
#define IMAG "i"
#define ROOT "√"
// #define PWR_TWO "²"

long long	safeAddition(long long n1, long long n2);
long long	safeSubtraction(long long n1, long long n2);
long long	safeMultiplication(long long n1, long long n2);
long long	safeDivision(long long n1, long long n2);

template<typename T, 
			typename std::enable_if<
			std::is_arithmetic<T>{}, bool>::type = true
		>
T			safeAbs(T n) {
	if (n == std::numeric_limits<T>::min()) {
		throw std::overflow_error("Cannot make " + std::to_string(n) + " positive without causing over- or underflow.\n");
	}
	return std::abs(n);
}

/* getGcd for all combinations of integral types */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
long long	getGcd(T a, U b) {
	auto gcd = std::gcd(a, b);
	return gcd == 0 ? 1: gcd; 
}


/* Default implementation of getGcd: if either parameter is floating point, return 1 */
template<typename T, typename U, 
			typename std::enable_if<
            std::is_floating_point<T>{} ||
            std::is_floating_point<U>{}, bool>::type = true
		>
long long 	getGcd(T a, U b) { 
	if (std::trunc((long double)a) == a
	&& (a <= (double)std::numeric_limits<long long>::max() && a >= (double)std::numeric_limits<long long>::min())
	&& std::trunc((long double)b) == b
	&& (b <= (double)std::numeric_limits<long long>::max() && b >= (double)std::numeric_limits<long long>::min())) {
		return (getGcd((long long)a, (long long)b));
	}
	return 1;
 }

template<typename T, typename U, typename V,
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{} &&
			std::is_integral<V>{}, bool>::type = true
		>
long long	getGcd(T a, U b, V c) {
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
		a = safeDivision(a, gcd);
		b = safeDivision(b, gcd);
	}
}

/* Overflow checks for arithmetic operations */
template<typename T, 
			typename std::enable_if<
            std::is_integral<T>{}, bool>::type = true
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
            std::is_integral<T>{}, bool>::type = true
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
            std::is_integral<T>{}, bool>::type = true
		>
bool	multiplicationExceedsLimits(T lhs, T rhs) {
	/* Check for over- and underflow */
	if (rhs == 0) return false;
	/* We have to separate this case because dividing numerical limit min by -1 
	will cause overflow in the check */
	if (rhs == -1 && lhs > 0) return false;
	return ((lhs > 0 && rhs > 0 && (lhs > std::numeric_limits<T>::max() / rhs))
	|| (lhs < 0 && rhs < 0 && (lhs < std::numeric_limits<T>::max() / rhs))
	|| (rhs > 0 && lhs < 0 && (lhs < std::numeric_limits<T>::min() / rhs))
	|| (rhs < -1 && lhs > 0 && (lhs > std::numeric_limits<T>::min() / rhs)));
}

template<typename T, 
			typename std::enable_if<
            std::is_integral<T>{}, bool>::type = true
		>
bool	divisionExceedsLimits(T lhs, T rhs) {
	return (lhs == std::numeric_limits<T>::min() && rhs == -1);
}

template<typename T, typename U, 
			typename std::enable_if<
            std::is_arithmetic<T>{} &&
            std::is_arithmetic<U>{}, bool>::type = true
		>
bool	additionExceedsLimits(T lhs, U rhs) {
	if (std::numeric_limits<T>::max() > std::numeric_limits<U>::max())
		return additionExceedsLimits(lhs, (T)rhs);
	else {
		return additionExceedsLimits((U)lhs, rhs);
	}
}

template<typename T, typename U, 
			typename std::enable_if<
            std::is_arithmetic<T>{} &&
            std::is_arithmetic<U>{}, bool>::type = true
		>
bool	subtractionExceedsLimits(T lhs, U rhs) {
	if (std::numeric_limits<T>::max() > std::numeric_limits<U>::max())
		return subtractionExceedsLimits(lhs, (T)rhs);
	else {
		return subtractionExceedsLimits((U)lhs, rhs);
	}
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
	if (trunc(value) < (double)LLONG_MIN || trunc(value) > (double)LLONG_MAX) {
		throw std::overflow_error("Whole part of decimal is too large to fit integer type\n"); }
	
	int				sign = value >= 0.0 ? 1 : -1;
	value = safeAbs(value);
	long long 		intPart = (long long)value;
	value -= intPart;

	/* Check whether number is within error margin from zero */
	if (-accuracy < value && accuracy > value) {
		return std::make_tuple(sign * intPart, 0, 1);
	}
	/* Check whether number is withing error margin from 1 */
	if ((1.0 - accuracy) < value && (1.0 + accuracy) > value) {
		return std::make_tuple(sign * (intPart + 1), 0, 1);
	}

	std::vector<long long> a = {1, 0};
	std::vector<long long> b = {0, 1};

	long double 		x = value;
	size_t				i = 1;
	do {
		++i;
		x = 1 / (x - trunc(x));
		long long next_a = safeAddition(a[i - 2], safeMultiplication(trunc(x), a[i - 1]));
		long long next_b = safeAddition(b[i - 2], safeMultiplication(trunc(x), b[i - 1]));
		a.push_back(next_a);
		b.push_back(next_b);
	}
	while (safeAbs(((long double)a[i] / (long double)b[i]) - value) > accuracy);

	if (a[i] == LLONG_MIN && sign == -1){
		throw std::overflow_error("Could not find rational approximation \
of decimal within given precision.");
	}
	long long whole = sign * intPart;
	long long denominator = b[i];
	long long numerator = sign * a[i];
	return	std::make_tuple(whole, numerator, denominator);
}

template<typename T, typename U, 
			typename std::enable_if<
            std::is_integral<T>{} &&
            std::is_integral<U>{}, bool>::type = true
		>
long long	intPow(T base, U exp) {
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

template<typename T, 
			typename std::enable_if<
			std::is_integral<T>{}, bool>::type = true
		>
bool		isPrime(T n) {
	/* Doesn't work for negative numbers */
	if (n < 2) {
		return false;
	}
	if (n == 2 || n == 3) {
		return true;
	}
	if (n % 2 == 0 || n % 3 == 0) {
		return false;
	}
	long long divisor = 6;
	// Based on the fact that every prime other than two and three is of the form
	// 6k+/-1
	while ((divisor * divisor) - ((divisor * 2) + 1) <= n) {
		if (n % (divisor - 1) == 0 || n % (divisor + 1) == 0) {
			return false;
		}
		divisor += 6;
	}
	return true;
}

template<typename T, 
			typename std::enable_if<
			std::is_integral<T>{}, bool>::type = true
		>
long long	findNextPrime(T n) {
	long long res = n;

	++res;
	// We only have to test odd numbers
	if (res % 2 == 0) {
		++res;
	}
	while (!isPrime(res)) {
		res += 2;
	}
	return res;
}

template<typename T, 
			typename std::enable_if<
			std::is_integral<T>{}, bool>::type = true
		>
std::vector<std::pair<long long, long long>>	getPrimeFactors(T n) {
	/* Returns vector of prime factors and how many times the occur */
	static std::vector<long long> primes = {2};
	auto prime_iter = primes.begin();
	long long prime = *prime_iter;

	std::vector<std::pair<long long, long long>> factors = {};
	while ((n >= prime * prime) && !isPrime(n)) {
		if (n % prime == 0) {
			if (!factors.empty() && std::get<0>(factors.back()) == prime) {
				std::get<1>(factors.back()) += 1;
			}
			else {
				factors.push_back(std::make_pair(prime, 1));
			}
			n /= prime;
		}
		else {
			// Check whether it's in the list
			if (std::distance(prime_iter, primes.end()) != 1) {
				// Means we have a next iterator
				++prime_iter;
			}
			else {
				primes.push_back(findNextPrime(prime));
				prime_iter = --(primes.end());
			}
			prime = *prime_iter;
		}
	}
	if (!factors.empty() && std::get<0>(factors.back()) == n) {
			std::get<1>(factors.back()) += 1;
	}
	else {
		factors.push_back(std::make_pair(n, 1));
	}
	return factors;
}

#endif
