#ifndef NUMERICAL_H
#define NUMERICAL_H
#include <variant>
#include <iostream>
#include "math_helpers.h"

typedef std::variant<int, long, long long, float, double, long double>	numerical;

class Numerical {
	public:
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Numerical(T n): _val{numerical(n)} {}
		Numerical(numerical n);
		Numerical(const Numerical &rhs);
		Numerical	&operator=(const Numerical &rhs);
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Numerical	&operator=(const T n) {
			setVal(n);
			return *this;
		}
		~Numerical() = default;

		bool			isIntegral() const;
		bool			isFloating() const;
		numerical		getVal() const;
		void			setVal(numerical n);

		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		void			setVal(T n) {
			_val = numerical(n);
		}
		operator 		long long() const;
		operator 		long double() const;
		operator		std::string () const;
		Numerical		operator-() const;
		Numerical		&operator+=(const Numerical &rhs);
		Numerical		&operator-=(const Numerical &rhs);
		Numerical		&operator*=(const Numerical &rhs);
		Numerical		&operator/=(const Numerical &rhs);
	private:
		numerical _val;
	
	friend Numerical			trunc(const Numerical &r);
	friend std::ostream    		&operator<<(std::ostream &os, const Numerical &x);
};

bool		operator==(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator==(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return (n == rhs);
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator==(const T &lhs, const Numerical &rhs) {
	return (rhs == lhs);
}

bool		operator!=(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator!=(const Numerical &lhs, const T &rhs) {
	return !(lhs == rhs);
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator!=(const T &lhs, const Numerical &rhs) {
	return (rhs == lhs);
}

bool		operator<(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator<(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return (n < rhs);
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator<(const T &lhs, const Numerical &rhs) {
	return !(rhs < lhs || rhs == lhs);
}

bool		operator<=(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator<=(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return (n <= rhs);
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator<=(const T &lhs, const Numerical &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator>(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator>(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return (n >= rhs);
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator>(const T &lhs, const Numerical &rhs) {
	return !(lhs < rhs);
}

bool		operator>=(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator>=(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return (n >= rhs);
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
bool		operator>=(const T &lhs, const Numerical &rhs) {
	return !(lhs < rhs);
}

Numerical	operator+(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator+(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return Numerical((n + rhs));
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator+(const T &lhs, const Numerical &rhs) {
	return (rhs + lhs);
}

Numerical	operator-(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator-(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return Numerical((n - rhs));
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator-(const T &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Numerical((lhs - n));
	}, lhs.getVal());
}

Numerical	operator*(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator*(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return Numerical((n * rhs));
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator*(const T &lhs, const Numerical &rhs) {
	return (rhs * lhs);
}

Numerical	operator/(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator/(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return Numerical((n / rhs));
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	operator/(const T &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Numerical((lhs / n));
	}, rhs.getVal());
}

Numerical	getGcd(const Numerical &lhs, const Numerical &rhs);
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	getGcd(const Numerical &lhs, const T &rhs) {
	return std::visit([=](auto n) {
		return Numerical(getGcd(n, rhs));
	}, lhs.getVal());
}
template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
Numerical	getGcd(const T &lhs, const Numerical &rhs) {
	return getGcd(rhs, lhs);
}

Numerical	abs(const Numerical &x);

#endif