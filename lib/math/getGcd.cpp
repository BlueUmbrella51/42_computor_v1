#include "math_helpers.h"

template <typename T, typename U>
long long		getGcd(T n, U m) {
	if (std::is_integral<T>::value && std::is_integral<U>::value)
		return std::gcd(n, m);
	return 1;
}

template<>	long long getGcd<long double, long double>(long double n, long double m);
template<>	long long getGcd<long double, double>(long double n, double m);
template<>	long long getGcd<long double, float>(long double n, float m);
template<>	long long getGcd<double, long double>(double n, long double m);
template<>	long long getGcd<float, long double>(float n, long double m);
template<>	long long getGcd<float, double>(float n, double m);
template<>	long long getGcd<double, float>(double n, float m);
template<>	long long getGcd<float, float>(float n, float m);
template<>	long long getGcd<double, double>(double n, double m);
