#ifndef RATIONAL_H
#define RATIONAL_H
#include <variant>
#include "math_helpers.h"
#include "Fraction.h"
// #include "Radical.h"

typedef	std::variant<int, long, long long, float, double, long double, Fraction> real;

class Rational {
	private:
		real	_val;

	public:
		Rational();
		Rational(real n);
		Rational(Fraction n);
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Rational(T n) : _val{real(n)}{}
		Rational(const Rational &rhs);
		~Rational() = default;
		Rational	&operator=(const Rational &rhs);

		operator 	std::string () const;
		// operator 	long double () const;
		Rational	operator-();
		Rational	&operator+=(const Rational &rhs);
		Rational	&operator-=(const Rational &rhs);
		Rational	&operator/=(const Rational &rhs);
		Rational	&operator*=(const Rational &rhs);
		real		getVal() const;

		bool		isIntegral();
		bool		isFloating();
		bool		isFraction();

		long double	toFloating();

	friend Rational				abs(const Rational &r);
	friend std::pair<Rational, Rational>	simplify_radical(const Rational &r, int degree);
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

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator==(const Rational &lhs, const T &n) {
// 	return (lhs == Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator==(const T &n, const Rational &rhs) {
// 	return (rhs == n);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator!=(const Rational &lhs, const T &n) {
// 	return !(lhs == n);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator!=(const T &n, const Rational &rhs) {
// 	return (rhs != n);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator<(const Rational &lhs, const T &n) {
// 	return (lhs < Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator<(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) < rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator<=(const Rational &lhs, const T &n) {
// 	return (lhs <= Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator<=(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) <= rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator>(const Rational &lhs, const T &n) {
// 	return (lhs > Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator>(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) > rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator>=(const Rational &lhs, const T &n) {
// 	return (lhs >= Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// bool	operator>=(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) >= rhs);
// }

// /* Arithmetic operators */
// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator+(const Rational &lhs, const T &n) {
// 	return (lhs + Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational		operator+(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) + rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator-(const Rational &lhs, const T &n) {
// 	return (lhs - Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator-(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) - rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator*(const Rational &lhs, const T &n) {
// 	return (lhs * Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator*(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) * rhs);
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator/(const Rational &lhs, const T &n) {
// 	return (lhs / Rational(real(n)));
// }

// template<typename T, 
// 			typename std::enable_if<
//             std::is_arithmetic<T>{}, bool>::type = true
// 		>
// Rational	operator/(const T &n, const Rational &rhs) {
// 	return (Rational(real(n)) / rhs);
// }

#endif