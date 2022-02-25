#include <stdio.h>

long int		gcd_inner(long int a, long int b, int sign) {
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (a == b)
		return (sign * a);
	if (a > b)
		return gcd_inner(a % b, b, sign);
	return gcd_inner(a, b % a, sign);
}

long int		gcd(long int a, long int b) {
	printf("A: %ld\nB: %ld\n", a, b);
	int sign = 1;
	if (a < 0 && b < 0) {
		a = -a;
		b = -b;
		sign = -1;
	}
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (a == b)
		return (sign * a);
	if (a > b)
		return gcd_inner(a % b, b, sign);
	return gcd_inner(a, b % a, sign);
}
