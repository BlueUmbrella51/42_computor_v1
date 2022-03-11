
#include "math_helpers.h"

void			ll_factor_gcd(long long *num, long long *denum) {
	long long gcd = std::gcd(*num, *denum);
	if (*denum < 0) {
		gcd *= -1;
	}
	if (gcd != 0) {
		if (gcd == -1 && (*num == LLONG_MIN || *denum == LLONG_MIN)) {
			throw std::overflow_error("Could not factor out gcd without causing overflow.");
		}
		*num /= gcd;
		*denum /= gcd;
	}
}
