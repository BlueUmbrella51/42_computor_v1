#include "math_helpers.h"
/* Stern-brocot algorithm for continued fractions
TODO: handle possible overflow? */


// Rational	doubleToRational(double value, double accuracy) {
// 	if (std::isinf(value) || std::isnan(value)) {
// 		throw std::invalid_argument("Argument to covert cannot be NaN or INF.");
// 	}
// 	if (accuracy < 0.0 || accuracy > 1.0) {
// 		throw std::invalid_argument("Accuracy must be number between 0.0 and 1.0.");
// 	}
// 	int	sign = value < 0.0 ? -1: 1;
// 	value = abs(value);
// 	long long unsigned int_part = (long long unsigned)value;
// 	// If there is no fractional part
// 	if (value == int_part) {
// 		return Rational(int_part, 1, sign);
// 	}
// 	double fractional_part = value - int_part;
// 	// Handle when we cannot approach the value further
// 	double minimal_value = fractional_part - (accuracy * value);
// 	double maximum_value = fractional_part + (accuracy * value);
// 	if (minimal_value < 0.0) {
// 		return Rational(int_part, 1, sign);
// 	}
// 	if (maximum_value > 1.0) {
// 		return (Rational(1 + int_part, 1, sign));
// 	}

// 	// Initially, we start with lower limit of 0/1 and upper limit of 1/1
// 	long long unsigned ln = 0;
// 	long long unsigned ld = 1;
// 	long long unsigned un = 1;
// 	long long unsigned ud = (long long unsigned)(1 / maximum_value);

// 	while (true) {
// 		// Update lowest fraction until we can't approach any further, n is number
// 		// of "steps" we can take
// 		long long unsigned n = (long long unsigned)((ld * minimal_value - ln) / (un - ud * minimal_value));

// 		// If we can't get closer anymore, we're done
// 		if (n == 0)
// 			break ;
		
// 		// Update left fraction
// 		ln += n * un;
// 		ld += n * ud;

// 		n = (long long unsigned)((un - ud * maximum_value) / (ld * maximum_value - ln));
// 		// If we cannot close in from the right (and also not from the left anymore) the loop ends
// 		if (n == 0) {
// 			break;
// 		}

// 		// Update right fraction
// 		un += n * ln;
// 		ud += n * ld;

// 		if (n == 0) {
// 			break;
// 		}
// 	}
// 	// The best approximation will be between ln/ld and un/ud, so ln+ud/ld+ud
// 	long long unsigned denom = ud + ld;
// 	// TODO: separate "whole" part of numerator?
// 	long long unsigned num = (denom * int_part) + ln + un;
// 	return (Rational(num, denom, sign));
// }
std::tuple<long long int, long long int>	doubleToRatio(long double value, long double accuracy) {
	if (std::isinf(value) || std::isnan(value)) {
		throw std::invalid_argument("Argument to covert cannot be NaN or INF.");
	}
	if (accuracy < 0.0 || accuracy > 1.0) {
		throw std::invalid_argument("Accuracy must be number between 0.0 and 1.0.");
	}
	int	sign = value >= 0.0 ? 1 : -1;
	// TODO: abs value
	double abs_val = std::abs(value);
	double dec_part = abs_val - floor(abs_val);

	// Handles integer numbers including 0.0
	if (abs_val == (long long)abs_val) {
		return std::make_tuple(sign * (long long)abs_val, 1);
	}
	std::vector<long long> a = {1, 0};
	std::vector<long long> b = {0, 1};

	double 		x = 1 / (abs_val - floor(abs_val));
	double 		z;
	size_t		i = 2;
	long long 	a_term, b_term = 0;
	double 		chk = 1.0;
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
