#ifndef FRACTION_H
#define FRACTION_H
#include <type_traits>
#include <ostream>
#include "math_helpers.h"
// #include "math_helpers.h"
// #include <limits.h>
// #include <float.h>
// #include "Types.h"
// #include <variant>

class	Fraction {
	private:
		long long						_w;
		long long	_n;
		long long						_d;
		void							simplify();
		void							fixSigns();
		Fraction						invert() const;
		
	public:
		Fraction();
		Fraction(long long whole);
		Fraction(long long n, long long d);
		// Fraction(Root n, long long d);
		Fraction(long long whole, long long n, long long d);
		~Fraction() = default;
		Fraction(const Fraction &rhs);
		long long									getWhole() const;
		long long				getNum() const;
		long long									getDenom() const;
		void										setNumerator(long long n);
		void										setDenominator(long long d);
		std::tuple<long long, long long, long long> getValue();
		operator long double () const;
		operator long long () const;
		operator std::string () const;

		Fraction	&operator=(const Fraction &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Fraction	&operator=(T n) {
			_w = n;
			_n = 0;
			_d = 1;
			return *this;
		}

		Fraction 	operator-() const;

		Fraction	&operator+=(const Fraction &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Fraction	&operator+=(T rhs) {
			Fraction tmp = Fraction(rhs);
			*this += tmp;
			return *this;
		}

		Fraction	&operator-=(const Fraction &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Fraction	&operator-=(T rhs) {
			Fraction tmp = Fraction(rhs);
			*this -= tmp;
			return *this;
		}
		
		Fraction	&operator/=(const Fraction &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Fraction	&operator/=(T rhs) {
			Fraction tmp = Fraction(rhs);
			*this /= tmp;
			return *this;
		}

		Fraction	&operator*=(const Fraction &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Fraction	&operator*=(T rhs) {
			Fraction tmp = Fraction(rhs);
			*this *= tmp;
			return *this;
		}
		Fraction 	getGcd() const;
		void		combineWholeNumerator();

	// friend std::pair<long long, Fraction>		simplifyRadical(const Fraction &r, int degree);
	friend Fraction								abs(const Fraction &rhs);
	friend Fraction								getGcd(const Fraction &lhs, const Fraction &rhs);
	friend Fraction								operator*(const Fraction &lhs, const Fraction &rhs);
	friend Fraction								operator/(const Fraction &lhs, const Fraction &rhs);
	friend Fraction								operator+(const Fraction &lhs, const Fraction &rhs);
	friend Fraction								operator-(const Fraction &lhs, const Fraction &rhs);
	friend std::ostream							&operator<<(std::ostream &os, const Fraction &r);
};

/* EQUALS */
bool		operator==(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator==(const T &n, const Fraction &r) {
	Fraction tmp = r;
	return (tmp.getWhole() == n && tmp.getNum() == 0);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator==(const Fraction &r, const T &n) {
	return (n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator==(const T &n, const Fraction &r) {
	return ((long double)r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator==(const Fraction &r, const T &n) {
	return (n == r);
}

/* NOT EQUAL */
bool		operator!=(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator!=(const T &n, const Fraction &r) {
	return !(n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator!=(const Fraction &r, const T &n) {
	return !(r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator!=(const T &n, const Fraction &r) {
	return !(n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator!=(const Fraction &r, const T &n) {
	return !(r == n);
}

/* GREATER THAN */
bool		operator>(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>(const T &n, const Fraction &r) {
	if (n > r.getWhole()) { return true; }
	if (n < r.getWhole()) { return false; }
	long long tmp_n = r.getWhole() < 0 ? -r.getNum(): r.getNum();
	return (tmp_n < 0);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>(const Fraction &r, const T &n) {
	return !(n > r || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>(const T &n, const Fraction &r) {
	return (n > (long double)r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>(const Fraction &r, const T &n) {
	return !(n > r || n == r);
}

/* GREATER OR EQUAL */
bool		operator>=(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>=(const T &n, const Fraction &r) {
	return (n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator>=(const Fraction &r, const T &n) {
	return (r > n || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>=(const T &n, const Fraction &r) {
	return (n >= (long double)r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator>=(const Fraction &r, const T &n) {
	return (r > n || r == n);
}

/* SMALLER THAN */

bool		operator<(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<(const T &n, const Fraction &r) {
	return !(n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<(const Fraction &r, const T &n) {
	return !(r > n || r == n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<(const T &n, const Fraction &r) {
	return !(n > r || n == r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<(const Fraction &r, const T &n) {
	return !(r > n || r == n);
}

/* SMALLER THAN OR EQUAL */

bool		operator<=(const Fraction &lhs, const Fraction &rhs);

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<=(const T &n, const Fraction &r) {
	return !(n > r);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
bool		operator<=(const Fraction &r, const T &n) {
	return !(r > n);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<=(const T &n, const Fraction &r) {
	return !(n > r);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool		operator<=(const Fraction &r, const T &n) {
	return !(r > n);
}

/* Floating point to rational */
template <typename T,
			typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true
		>
Fraction        doubleToFraction(T n, long double accuracy = 0.0) {
    try {
        auto [ whole, numerator, denominator ] = doubleToRatio(n, accuracy);
		return Fraction(whole, numerator, denominator);
    }
    catch (std::overflow_error &e) {
        throw;
    }
}

/*  GET GCD INT */
template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
Fraction	getGcd(const Fraction &a, const T &b) {
	auto nw = Fraction(b);
	return (getGcd(nw, a));
}

template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
Fraction	getGcd(const T &a, const Fraction &b) {
	return	getGcd(b, a);
}

/* MULTIPLY BY INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator*(const Fraction &lhs, const T &rhs) {
	Fraction tmp = lhs;
	tmp *= rhs;
	return tmp;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator*(const T &lhs, const Fraction &rhs) {
	return (rhs * lhs);
}

/* MULTIPLY BY FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator*(const Fraction &lhs, const T &rhs) {
	// TODO: simplify
	return ((long double)lhs * rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator*(const T &lhs, const Fraction &rhs) {
	return (rhs * lhs);
}

/* DIVIDE BY INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator/(const Fraction &lhs, const T &rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Division by zero requested\n");
	}
	Fraction tmp = Fraction(rhs);
	return (lhs * tmp);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator/(const T &lhs, const Fraction &rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Division by zero requested\n");
	}
	Fraction	tmp = Fraction(lhs);
	return tmp / rhs;
}

/* DIVIDE BY FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator/(const Fraction &lhs, const T &rhs) {
	return ((long double)lhs / rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator/(const T &lhs, const Fraction &rhs) {
	return (rhs / lhs);
}

/* ADD INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator+(const Fraction &lhs, const T &rhs) {
	// Copy lhs, then add rhs
	Fraction n = lhs;
	n += rhs;
	return n;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator+(const T &lhs, const Fraction &rhs) {
	return (rhs + lhs);
}

/* ADD FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator+(const Fraction &lhs, const T &rhs) {
	// TODO: simplify
	long double n = (long double)lhs;
	// assert(!((rhs >= 0 && n > LDBL_MAX - rhs) ||
	// (n && n < LDBL_MIN - n)));
	return (n + rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator+(const T &lhs, const Fraction &rhs) {
	return (rhs + lhs);
}

/* SUBTRACT INT */
template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator-(const Fraction &lhs, const T &rhs) {
	Fraction n = lhs;
	n -= rhs;
	return lhs;
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Fraction	operator-(const T &lhs, const Fraction &rhs) {
	Fraction n = Fraction(lhs);
	n -= rhs;
	return n;
}

/* SUBTRACT FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(const Fraction &lhs, const T &rhs) {
	// long double n = (long double)lhs;
	// assert(!((rhs < 0 && n > LDBL_MAX + rhs) 
	// || (rhs >= 0 && lhs < LDBL_MIN + rhs)));
	return ((long double)lhs - rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(const T &lhs, const Fraction &rhs) {
	return (rhs - lhs);
}

std::tuple<long long, long long, long long>	getDenomFactorsLcm(long long d_left, long long d_right);
std::tuple<long long, long long>	getDenomFactors(long long d_left, long long d_right);

#endif
