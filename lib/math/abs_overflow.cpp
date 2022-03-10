#include "math_helpers.h"

template <typename T>
std::optional<T>	abs_overflow(T n) {
	if (n < 0) {
		T prev = n;
		n = llabs(n);
		if (n / -1 != prev) { return std::nullopt; }
		return n;
	}
	return n;
}
