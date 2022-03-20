#ifndef RATIONAL_H
#define RATIONAL_H
#include <type_traits>
#include <ostream>
#include "math_helpers.h"
#include <limits.h>
#include <float.h>

class	Rational {
	private:
		void							simplify();
		void							fixSigns();
		Rational						invert() const;
		std::tuple<long long, long long, long long>	getDenomFactors(long long d_left, long long d_right);
		
	public:
		Rational();
		Rational(long long n, long long d);
		Rational(long long whole, long long n, long long d);
		~Rational() = default;
		Rational(const Rational &rhs);
		operator long double () const;
		operator long long () const;
		
		Rational 	&operator-();
		
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

		bool		operator==(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator==(T n) const {
			return (_w == n && _n == 0);
		}

		bool		operator!=(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator!=(T n) const {
			return !(*this == n);
		}

		bool		operator>(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator>(T n) const {
			if (_w > n) { return true; }
			if (_w < n) { return false; }
			long long tmp_n = _w < 0 ? -_n: _n;
			return (tmp_n > 0);
		}

		bool		operator>=(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator>=(T n) const {
			return (*this > n || *this == n);
		}

		bool		operator<(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator<(T n) const {
			// If whole part < n, this is true. if n == _w, we have to check 
			// fractional part
			if (_w < n) { return true; }
			if (_w > n) { return false; }
			long long tmp_n = _w < 0 ? -_n: _n;
			return (tmp_n < 0);
		}

		bool		operator<=(const Rational &rhs) const;
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		bool		operator<=(T n) const {
			return (*this < n || *this == n);
		}

		Rational	&operator+=(const Rational &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator+=(T rhs) {
			// a += b
			if (*this == 0) {
				*this = rhs;
			}
			else if (*this < 0 && rhs >= 0) {
				/* 	If a < 0 and b >= 0: -a + b == b - abs(a) */
				*this = rhs - *this;
			}
			else if (rhs < 0) {
				/* a + - b == a - abs(b)*/
				*this -= llabs(rhs);
			}
			else {
				/* Both a and b >= 0 */
				// Calculate new whole part
				 _w += rhs;
			}
			return *this;
		}

		Rational	&operator-=(const Rational &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator-=(T rhs) {
			if (*this == 0) {
				*this = -rhs;
			}
			else if (rhs < 0) {
				/* a -(-b) == a + b */
				*this -= llabs(rhs);
			}
			else if (*this < 0) {
				/* a < 0 && b >= 0 => -a -b == -(abs(a) + b)*/
				*this = -(abs(*this) + rhs);
			}
			else if (*this < rhs) {
				/* if a and b both >= 0 and b > a, calculate -(b - a) */
				*this = -(rhs - *this);
			}
			else {
				/* Both a and b >= 0 AND b is guaranteed to be >= a
				Therefore, we can never go below 0 so no need to adjust 
				fraction ever. */
				_w -= rhs;
			}
			return *this;
		}
		
		Rational	&operator/=(const Rational &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator/=(T rhs) {
			// TODO
			return *this;
		}

		Rational	&operator*=(const Rational &rhs);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Rational	&operator*=(T rhs) {
			if (*this == 0 || rhs == 0) {
				*this = 0;
			}
			else if (*this < 0 || rhs < 0) {
				/* If both terms < 0, discard the -1 */
				if (*this == 0 && rhs == 0) {
					*this = abs(*this) * llabs(rhs);
				}
				else {
					/* If either term is < 0, we take out the - and add it 
					back in after calculation. */
					*this = -(abs(*this) * llabs(rhs));
				}
			}
			else {
				_w *= rhs;
				_n *= rhs;
				// Takes whole parts out of numerator and simplifies fraction
				simplify();
			}
			return *this;
		}

		long long	_n;
		long long	_d;
		long long	_w;
		Rational 	getGcd() const;

	friend Rational		abs(const Rational &rhs);
	friend Rational		getGcd(const Rational &lhs, const Rational &rhs);
	friend Rational		operator*(const Rational &lhs, const Rational &rhs);
	friend Rational		operator/(const Rational &lhs, const Rational &rhs);
	friend Rational		operator+(const Rational &lhs, const Rational &rhs);
	friend Rational		operator-(const Rational &lhs, const Rational &rhs);
	friend std::ostream	&operator<<(std::ostream &os, const Rational &r);
};

/* Floating point to rational */
template <typename T,
			typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true
		>
Rational        doubleToRational(T n, long double accuracy = 0.0) {
    try {
        auto [ whole, numerator, denominator ] = doubleToRatio(n, accuracy);
		return Rational(numerator, denominator, whole);
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
	auto nw = Rational(b, 1);
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
	Rational tmp = Rational(1, rhs);
	return (lhs * tmp);
}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
Rational	operator/(const T &lhs, const Rational &rhs) {
	Rational	tmp = Rational(1, lhs);
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
	return lhs;
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
	Rational n = Rational(0, 1, lhs);
	n -= rhs;
	return n;
}

/* SUBTRACT FLOAT */
template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(Rational &lhs, const T &rhs) {
	long double n = (long double)lhs;
	assert(!((rhs < 0 && n > LDBL_MAX + rhs) 
	|| (rhs >= 0 && lhs < LDBL_MIN + rhs)));
	return ((long double)lhs - rhs);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
long double	operator-(const T &lhs, const Rational &rhs) {
	return (rhs - lhs);
}


#endif
