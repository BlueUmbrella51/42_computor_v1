#ifndef RATIONAL_H
#define RATIONAL_H
#include <variant>
#include "math_helpers.h"
#include "Fraction.h"
#include "Numerical.h"

typedef	std::variant<Numerical, Fraction> real;

class Rational {
	private:
		real	_val;

	public:
		Rational();
		Rational(Numerical n);
		Rational(Fraction n);
		Rational(const Rational &rhs);
		template<typename T,
			std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Rational(T n) : _val{Numerical(n)}{}
		~Rational() = default;
		Rational	&operator=(const Rational &rhs);

		operator 	std::string () const;
		operator	long long () const;
		operator 	long double () const;
		Rational	operator-();
		Rational	&operator+=(const Rational &rhs);
		Rational	&operator-=(const Rational &rhs);
		Rational	&operator/=(const Rational &rhs);
		Rational	&operator*=(const Rational &rhs);
		real		getVal() const;

		bool		isIntegral() const;
		bool		isFloating() const;
		bool		isFraction() const;

	friend Rational				trunc(const Rational &r);
	friend Rational				abs(const Rational &r);
	friend Rational				operator*(const Rational &a, const Rational &b);
	friend Rational				operator/(const Rational &a, const Rational &b);
	friend Rational				operator+(const Rational &a, const Rational &b);
	friend Rational				operator-(const Rational &a, const Rational &b);
	friend std::ostream    		&operator<<(std::ostream &os, const Rational &x);
	friend Rational				getGcd(const Rational &a, const Rational &b);
	friend bool					operator==(const Rational &lhs, const Rational &rhs);
	friend bool					operator!=(const Rational &lhs, const Rational &rhs);
	friend bool					operator>=(const Rational &lhs, const Rational &rhs);
	friend bool					operator>(const Rational &lhs, const Rational &rhs);
	friend bool					operator<(const Rational &lhs, const Rational &rhs);
	friend bool					operator<=(const Rational &lhs, const Rational &rhs);
};

bool		operator==(const Numerical &lhs, const Fraction &rhs);
bool		operator==(const Fraction &lhs, const Numerical &rhs);
bool		operator!=(const Numerical &lhs, const Fraction &rhs);
bool		operator!=(const Fraction &lhs, const Numerical &rhs);
bool		operator<(const Numerical &lhs, const Fraction &rhs);
bool		operator<(const Fraction &lhs, const Numerical &rhs);
bool		operator<=(const Numerical &lhs, const Fraction &rhs);
bool		operator<=(const Fraction &lhs, const Numerical &rhs);
bool		operator>(const Numerical &lhs, const Fraction &rhs);
bool		operator>(const Fraction &lhs, const Numerical &rhs);
bool		operator>=(const Numerical &lhs, const Fraction &rhs);
bool		operator>=(const Fraction &lhs, const Numerical &rhs);

Rational	operator+(const Numerical &lhs, const Fraction &rhs);
Rational	operator+(const Fraction &lhs, const Numerical &rhs);
Rational	operator-(const Numerical &lhs, const Fraction &rhs);
Rational	operator-(const Fraction &lhs, const Numerical &rhs);
Rational	operator*(const Numerical &lhs, const Fraction &rhs);
Rational	operator*(const Fraction &lhs, const Numerical &rhs);
Rational	operator/(const Numerical &lhs, const Fraction &rhs);
Rational	operator/(const Fraction &lhs, const Numerical &rhs);

bool		operator==(const Numerical &lhs, const Rational &rhs);
bool		operator==(const Rational &lhs, const Numerical &rhs);
bool		operator!=(const Numerical &lhs, const Rational &rhs);
bool		operator!=(const Rational &lhs, const Numerical &rhs);
bool		operator<(const Numerical &lhs, const Rational &rhs);
bool		operator<(const Rational &lhs, const Numerical &rhs);
bool		operator<=(const Numerical &lhs, const Rational &rhs);
bool		operator<=(const Rational &lhs, const Numerical &rhs);
bool		operator>(const Numerical &lhs, const Rational &rhs);
bool		operator>(const Rational &lhs, const Numerical &rhs);
bool		operator>=(const Numerical &lhs, const Rational &rhs);
bool		operator>=(const Rational &lhs, const Numerical &rhs);

Rational	operator+(const Numerical &lhs, const Rational &rhs);
Rational	operator+(const Rational &lhs, const Numerical &rhs);
Rational	operator-(const Numerical &lhs, const Rational &rhs);
Rational	operator-(const Rational &lhs, const Numerical &rhs);
Rational	operator*(const Numerical &lhs, const Rational &rhs);
Rational	operator*(const Rational &lhs, const Numerical &rhs);
Rational	operator/(const Numerical &lhs, const Rational &rhs);
Rational	operator/(const Rational &lhs, const Numerical &rhs);

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator==(const Rational &lhs, const T &n) {
	return (lhs == Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator==(const T &n, const Rational &rhs) {
	return (rhs == n);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator!=(const Rational &lhs, const T &n) {
	return !(lhs == n);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator!=(const T &n, const Rational &rhs) {
	return (rhs != n);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator<(const Rational &lhs, const T &n) {
	return (lhs < Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator<(const T &n, const Rational &rhs) {
	return (Rational(n) < rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator<=(const Rational &lhs, const T &n) {
	return (lhs <= Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator<=(const T &n, const Rational &rhs) {
	return (Rational(n) <= rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator>(const Rational &lhs, const T &n) {
	return (lhs > Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator>(const T &n, const Rational &rhs) {
	return (Rational(n) > rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator>=(const Rational &lhs, const T &n) {
	return (lhs >= Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
bool	operator>=(const T &n, const Rational &rhs) {
	return (Rational(n) >= rhs);
}

// /* Arithmetic operators */
template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator+(const Rational &lhs, const T &n) {
	return (lhs + Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational		operator+(const T &n, const Rational &rhs) {
	return (Rational(n) + rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator-(const Rational &lhs, const T &n) {
	return (lhs - Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator-(const T &n, const Rational &rhs) {
	return (Rational(n) - rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator*(const Rational &lhs, const T &n) {
	return (lhs * Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator*(const T &n, const Rational &rhs) {
	return (Rational(n) * rhs);
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator/(const Rational &lhs, const T &n) {
	return (lhs / Rational(n));
}

template<typename T, 
			typename std::enable_if<
            std::is_arithmetic<T>{}, bool>::type = true
		>
Rational	operator/(const T &n, const Rational &rhs) {
	return (Rational(n) / rhs);
}

#endif