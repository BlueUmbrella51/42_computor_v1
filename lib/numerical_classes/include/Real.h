#ifndef REAL_H
#define REAL_H
#include <variant>
#include "Rational.h"
#include "math_helpers.h"

typedef	std::variant<int, long, long long, float, double, long double, Rational> real;

class Real {
	private:
		real	_val;

	public:
		Real(real n);
		Real(Rational n);
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Real(T n) : _val{real(n)}{}
		Real(const Real &rhs);
		~Real() = default;
		Real	&operator=(const Real &rhs);

		operator std::string () const;
		Real	operator-();
		Real	&operator+=(const Real &rhs);
		Real	&operator-=(const Real &rhs);
		Real	&operator/=(const Real &rhs);
		Real	&operator*=(const Real &rhs);
		real	getVal() const;

	friend Real				operator*(const Real &a, const Real &b);
	friend Real				operator/(const Real &a, const Real &b);
	friend Real				operator+(const Real &a, const Real &b);
	friend Real				operator-(const Real &a, const Real &b);
	friend std::ostream    	&operator<<(std::ostream &os, const Real &x);
	friend Real				getGcd(const Real &a, const Real &b);
	friend bool				operator==(const Real &lhs, const Real &rhs);
	friend bool				operator!=(const Real &lhs, const Real &rhs);
	friend bool				operator>=(const Real &lhs, const Real &rhs);
	friend bool				operator>(const Real &lhs, const Real &rhs);
	friend bool				operator<(const Real &lhs, const Real &rhs);
	friend bool				operator<=(const Real &lhs, const Real &rhs);
};

#endif