#ifndef RATIONAL_H
#define RATIONAL_H
#include <type_traits>
#include <ostream>
#include "math_helpers.h"
#include <limits.h>
#include <float.h>

class	Rational {
	private:
		long long	_w;
		long long	_n;
		long long	_d;
		void							simplify();
		void							fixSigns();
		Rational						invert() const;
		
	public:
		Rational();
		Rational(long long whole);
		Rational(long long n, long long d);
		Rational(long long whole, long long n, long long d);
		~Rational() = default;
		Rational(const Rational &rhs);
		long long	getWhole() const;
		long long	getNum() const;
		long long	getDenom() const;
		std::tuple<long long, long long, long long> getValue();
		operator long double () const;
		operator long long () const;
		operator std::string () const;
		
		Rational	&operator=(const Rational &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator=(T n) {
			_w = n;
			_n = 0;
			_d = 1;
			return *this;
		}

		Rational 	operator-() const;

		Rational	&operator+=(const Rational &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator+=(T rhs) {
			Rational tmp = Rational(rhs);
			*this += tmp;
			return *this;
		}

		Rational	&operator-=(const Rational &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator-=(T rhs) {
			Rational tmp = Rational(rhs);
			*this -= tmp;
			return *this;
		}
		
		Rational	&operator/=(const Rational &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator/=(T rhs) {
			Rational tmp = Rational(rhs);
			*this /= tmp;
			return *this;
		}

		Rational	&operator*=(const Rational &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator*=(T rhs) {
			Rational tmp = Rational(rhs);
			*this *= tmp;
			return *this;
		}
		Rational 	getGcd() const;

	friend Rational		simplify_radical(Rational &r, int degree);
	friend Rational		abs(const Rational &rhs);
	friend Rational		getGcd(const Rational &lhs, const Rational &rhs);
	friend Rational		operator*(const Rational &lhs, const Rational &rhs);
	friend Rational		operator/(const Rational &lhs, const Rational &rhs);
	friend Rational		operator+(const Rational &lhs, const Rational &rhs);
	friend Rational		operator-(const Rational &lhs, const Rational &rhs);
	friend std::ostream	&operator<<(std::ostream &os, const Rational &r);
};

/* EQUALS */
bool		operator==(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator==(const T &n, const Rational &r) {
	return (r.getWhole() == n && r.getNum() == 0);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator==(const Rational &r, const T &n) {
	return (n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator==(const T &n, const Rational &r) {
	return ((long double)r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator==(const Rational &r, const T &n) {
	return (n == r);
}

/* NOT EQUAL */
bool		operator!=(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator!=(const T &n, const Rational &r) {
	return !(n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator!=(const Rational &r, const T &n) {
	return !(r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator!=(const T &n, const Rational &r) {
	return !(n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator!=(const Rational &r, const T &n) {
	return !(r == n);
}

/* GREATER THAN */
bool		operator>(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>(const T &n, const Rational &r) {
	if (n > r.getWhole()) { return true; }
	if (n < r.getWhole()) { return false; }
	long long tmp_n = r.getWhole() < 0 ? -r.getNum(): r.getNum();
	return (tmp_n < 0);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>(const Rational &r, const T &n) {
	return !(n > r || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>(const T &n, const Rational &r) {
	return (n > (long double)r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>(const Rational &r, const T &n) {
	return !(n > r || n == r);
}

/* GREATER OR EQUAL */
bool		operator>=(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>=(const T &n, const Rational &r) {
	return (n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>=(const Rational &r, const T &n) {
	return (r > n || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>=(const T &n, const Rational &r) {
	return (n >= (long double)r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>=(const Rational &r, const T &n) {
	return (r > n || r == n);
}

/* SMALLER THAN */

bool		operator<(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<(const T &n, const Rational &r) {
	return !(n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<(const Rational &r, const T &n) {
	return !(r > n || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<(const T &n, const Rational &r) {
	return !(n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<(const Rational &r, const T &n) {
	return !(r > n || r == n);
}

/* SMALLER THAN OR EQUAL */

bool		operator<=(const Rational &lhs, const Rational &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<=(const T &n, const Rational &r) {
	return !(n > r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<=(const Rational &r, const T &n) {
	return !(r > n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<=(const T &n, const Rational &r) {
	return !(n > r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<=(const Rational &r, const T &n) {
	return !(r > n);
}

/* Floating point to rational */
template <typename T,
			typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true
		>
Rational        doubleToRational(T n, long double accuracy = 0.0) {
    try {
        auto [ whole, numerator, denominator ] = doubleToRatio(n, accuracy);
		return Rational(whole, numerator, denominator);
    }
    catch (std::overflow_error &e) {
        throw;
    }
}

/*  GET GCD INT */
template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
Rational	getGcd(const Rational &a, const T &b) {
	auto nw = Rational(b);
	return (getGcd(nw, a));
}

template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
Rational	getGcd(const T &a, const Rational &b) {
	return	getGcd(b, a);
}

/* MULTIPLY BY INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator*(const Rational &lhs, const T &rhs) {
	Rational tmp = lhs;
	tmp *= rhs;
	return tmp;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator*(const T &lhs, const Rational &rhs) {
	return (rhs * lhs);
}

/* MULTIPLY BY FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator*(const Rational &lhs, const T &rhs) {
	// TODO: simplify
	return ((long double)lhs * rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator*(const T &lhs, const Rational &rhs) {
	return (rhs * lhs);
}

/* DIVIDE BY INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator/(const Rational &lhs, const T &rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Division by zero requested\n");
	}
	Rational tmp = Rational(rhs);
	return (lhs * tmp);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator/(const T &lhs, const Rational &rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Division by zero requested\n");
	}
	Rational	tmp = Rational(lhs);
	return tmp / rhs;
}

/* DIVIDE BY FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator/(const Rational &lhs, const T &rhs) {
	return ((long double)lhs / rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator/(const T &lhs, const Rational &rhs) {
	return (rhs / lhs);
}

/* ADD INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator+(const Rational &lhs, const T &rhs) {
	// Copy lhs, then add rhs
	Rational n = lhs;
	n += rhs;
	return n;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator+(const T &lhs, const Rational &rhs) {
	return (rhs + lhs);
}

/* ADD FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator+(const Rational &lhs, const T &rhs) {
	// TODO: simplify
	long double n = (long double)lhs;
	assert(!((rhs >= 0 && n > LDBL_MAX - rhs) ||
	(n && n < LDBL_MIN - n)));
	return (n + rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator+(const T &lhs, const Rational &rhs) {
	return (rhs + lhs);
}

/* SUBTRACT INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator-(const Rational &lhs, const T &rhs) {
	Rational n = lhs;
	n -= rhs;
	return lhs;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator-(const T &lhs, const Rational &rhs) {
	Rational n = Rational(lhs);
	n -= rhs;
	return n;
}

/* SUBTRACT FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(const Rational &lhs, const T &rhs) {
	long double n = (long double)lhs;
	assert(!((rhs < 0 && n > LDBL_MAX + rhs) 
	|| (rhs >= 0 && lhs < LDBL_MIN + rhs)));
	return ((long double)lhs - rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(const T &lhs, const Rational &rhs) {
	return (rhs - lhs);
}

std::tuple<long long, long long, long long>	getDenomFactorsLcm(long long d_left, long long d_right);
std::tuple<long long, long long>	getDenomFactors(long long d_left, long long d_right);

#endif
