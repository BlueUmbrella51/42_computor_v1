#include "math_helpers.h"

long long		getGcd(long double lhs, long double rhs) {
	/* Just to return one without compiler errors */
	return 1;
}

long long		getGcd(long double lhs, long long rhs) {
	return 1;
}

long long		getGcd(long long lhs, long double rhs) {
	return 1;
}

long long 		getGcd(long long lhs, long long rhs) {
	return std::gcd(lhs, rhs);
}
