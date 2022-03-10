#include "math_helpers.h"

template <typename T>
std::optional<T> pow_overflow(T base, int exp)
{
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
