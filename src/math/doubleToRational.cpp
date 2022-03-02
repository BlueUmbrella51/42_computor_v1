#include "headers/math_helpers.hpp"
/* Stern-brocot algorithm for continued fractions
TODO: handle possible overflow? */

Rational        doubleToRational(double num, double accuracy) {
	/* accuracy determines how far (as a percentage) off the value we choose can be from the value of num */
	if (std::isinf(num) || std::isnan(num)) {
		throw std::invalid_argument("Argument to convert to rational cannot be NaN or INF");
	}
	if (accuracy <= 0.0 || accuracy >= 1.0) {
        throw std::invalid_argument("Accuracy must be > 0 and < 1.");
    }
	int sign = num > 0 ? 1: -1;
	num = abs(num);
	double error = sign == -1 ? accuracy : num * accuracy;
	long int n = long(floor(num));
	num -= n;
	if (num < error) {
		return (Rational(sign * n, 1));
	}
	else if (1 - error < num) {
		return (Rational(sign * (n + 1), 1));
	}
	// lower bound is 0/1
	long int lower_n = 0;
	long int lower_d = 1;
	// higher bound is 1/0
	long int	higher_n = 1;
	long int 	higher_d = 0;
	while (true) {
		long int middle_n = lower_n + higher_n;
		long int middle_d = lower_d + higher_d;

        if ((middle_d * (num + error)) < middle_n) {
			if (((lower_d + higher_d) * (num + error)) < (lower_n + higher_n)) {
				int weight = 1;
				do
				{
					weight *= 2;
					higher_n += lower_n * weight;
					higher_d += lower_d * weight;
				}
				while (((lower_d + higher_d) * (num + error)) < (lower_n + higher_n));
				do {
					weight /= 2;
					long int n_off = lower_n * weight;
					long int d_off = lower_d * weight;

					if (!(((lower_d + (higher_d - d_off)) * (num + error)) < (lower_n + (higher_n - n_off))))
					{
						higher_n -= n_off;
						higher_d -= d_off;
					}
				}
				while (weight > 1);
			}
		}
        // Else If middle < x - error
        else if (middle_n < ((num - error) * middle_d)) {
			if ((lower_n + higher_n) < ((num - error) * (lower_d + higher_d))) {
				int weight = 1;
				do
				{
					weight *= 2;
					lower_n += higher_n * weight;
					lower_d += higher_d * weight;
				}
				while ((lower_n + higher_n) < ((num - error) * (lower_d + higher_d)));
				do {
					weight /= 2;
					long int n_off = higher_n * weight;
					long int d_off = higher_d * weight;

					if (!(((lower_n - n_off) + higher_n) < ((num - error) * ((lower_d - d_off) + higher_d))))
					{
						lower_n -= n_off;
						lower_d -= d_off;
					}
				}
				while (weight > 1);
			}
		}
        // Else closest fraction has been found
        else {
            return (Rational((n * middle_d + middle_n) * sign, middle_d));
		}
	}
}