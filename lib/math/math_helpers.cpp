
#include "math_helpers.h"

long long	safeAddition(long long n1, long long n2) {
	if (additionExceedsLimits(n1, n2)) {
		std::string err = "Cannot perform addition of " + std::to_string(n1) + " and " +
		std::to_string(n2) + " without causing overflow.\n";
		throw std::overflow_error(err);
	}
	return n1 + n2;
}

long long	safeSubtraction(long long n1, long long n2) {
	if (subtractionExceedsLimits(n1, n2)) {
		std::string err = "Cannot perform subtraction of " + std::to_string(n1) + " and " +
		std::to_string(n2) + " without causing overflow.\n";
		throw std::overflow_error(err);
	}
	return n1 - n2;
}

long long	safeMultiplication(long long n1, long long n2) {
	if (multiplicationExceedsLimits(n1, n2)) {
		std::string err = "Cannot perform multiplication of " + std::to_string(n1) + " and " +
		std::to_string(n2) + " without causing overflow.\n";
		throw std::overflow_error(err);
	}
	return n1 * n2;
}

long long	safeDivision(long long n1, long long n2) {
	if (divisionExceedsLimits(n1, n2)) {
		std::string err = "Cannot perform division of " + std::to_string(n1) + " and " +
		std::to_string(n2) + " without causing overflow.\n";
		throw std::overflow_error(err);
	}
	return n1 / n2;
}

// long long	safeAbs(long long n) {
// 	if (n == LLONG_MIN) {
// 		throw std::overflow_error("Cannot make " + std::to_string(n) + " positive without causing overflow.\n");
// 	}
// 	return llabs(n);
// }