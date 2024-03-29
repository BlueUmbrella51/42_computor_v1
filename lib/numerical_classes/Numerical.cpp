#include "Numerical.h"
#include <cfenv>

Numerical::Numerical(numerical n): _val{n} {
}

Numerical::Numerical(const Numerical &rhs) : _val{rhs._val} {
}

Numerical	&Numerical::operator=(const Numerical &rhs) {
	if (this != &rhs) {
		_val = rhs._val;
	}
	return *this;
}

bool			Numerical::isIntegral() const {
	return (std::holds_alternative<int>(_val)
	|| std::holds_alternative<long>(_val)
	|| std::holds_alternative<long long>(_val));
}

bool			Numerical::isFloating() const {
	return !isIntegral();
}

numerical		Numerical::getVal() const {
	return _val;
}

void			Numerical::setVal(numerical n) {
	_val = n;
}

Numerical::operator		long long() const {
	return std::visit([](auto n) {
		return (long long)n;
	}, getVal());
}

Numerical::operator		long double() const {
	return std::visit([](auto n) {
		return (long double)n;
	}, getVal());
}

Numerical::operator		std::string() const {
	return std::visit([](auto n) {
		if (trunc(n) == n && (long long)n == trunc(n)) {
			return std::to_string((long long)n);
		}
		else {
			return std::to_string(n);
		}
	}, getVal());
}

Numerical		Numerical::operator-() const {
	return std::visit([](auto n) {
		numerical res = numerical(-n);
		if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW)) {
			throw std::overflow_error("Cannot perform -" + std::to_string(n) + " without causing over- or underflow.\n");
		}
		return res;
	}, getVal());
}

Numerical		&Numerical::operator+=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		numerical res = n1 + n2;
		if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW)) {
			throw std::overflow_error("Cannot add " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing over- or underflow.\n");
		}
		return res;
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator-=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		numerical res = n1 - n2;
		if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW)) {
			throw std::overflow_error("Cannot subtract " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing over- or underflow.\n");
		}
		return res;
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator*=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		numerical res = n1 * n2;
		if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW))  {
			throw std::overflow_error("Cannot multiply " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing over- or underflow.\n");
		}
		return res;
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator/=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		numerical res = n1 / n2;
		if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW)) {
			throw std::overflow_error("Cannot divide " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing over- or underflow.\n");
		}
		return res;
	}, _val, rhs._val);
	return *this;
}

Numerical		trunc(const Numerical &r) {
	return std::visit([](auto n) {
		return Numerical(std::trunc(n));
	}, r.getVal());
}

std::ostream    		&operator<<(std::ostream &os, const Numerical &x) {
	std::visit([&os](auto &n) {
		os << n;
	}, x._val);
	return os;
}

bool		operator==(const Numerical &lhs, const Numerical &rhs) {
	return std::visit([](auto n1, auto n2) {
		return (n1 == n2);
	}, lhs.getVal(), rhs.getVal());
}

bool		operator!=(const Numerical &lhs, const Numerical &rhs) {
	return !(lhs == rhs);
}

bool		operator<(const Numerical &lhs, const Numerical &rhs) {
	return std::visit([](auto n1, auto n2) {
		return (n1 < n2);
	}, lhs.getVal(), rhs.getVal());
}

bool		operator<=(const Numerical &lhs, const Numerical &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator>(const Numerical &lhs, const Numerical &rhs) {
	return !(lhs < rhs || lhs == rhs);
}

bool		operator>=(const Numerical &lhs, const Numerical &rhs) {
	return !(lhs < rhs);
}

Numerical	operator+(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp += rhs;
}

Numerical	operator-(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp -= rhs;
}

Numerical	operator*(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp *= rhs;
}

Numerical	operator/(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp /= rhs;
}

Numerical	getGcd(const Numerical &lhs, const Numerical &rhs) {
	return std::visit([](auto n1, auto n2) {
		return Numerical(getGcd(n1, n2));
	}, lhs.getVal(), rhs.getVal());
}

Numerical	abs(const Numerical &x) {
	return std::visit([](auto n) {
		return Numerical(safeAbs(n));
	}, x.getVal());
}
