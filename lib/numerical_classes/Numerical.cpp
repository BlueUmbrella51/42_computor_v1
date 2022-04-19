#include "Numerical.h"

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
		return std::to_string(n);
	}, getVal());
}

Numerical		Numerical::operator-() const {
	return std::visit([](auto n) {
		if (multiplicationExceedsLimits(n, -1)) {
			throw std::overflow_error("Cannot perform -" + std::to_string(n) + " without causing overflow.\n");
		}
		return Numerical(-n);
	}, getVal());
}

Numerical		&Numerical::operator+=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		if (additionExceedsLimits(n1, n2)) {
			throw std::overflow_error("Cannot add " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing overflow.\n");
		}
		return numerical((n1 + n2));
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator-=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		if (subtractionExceedsLimits(n1, n2)) {
			throw std::overflow_error("Cannot subtract " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing overflow.\n");
		}
		return numerical((n1 - n2));
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator*=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		if (multiplicationExceedsLimits(n1, n2)) {
			throw std::overflow_error("Cannot multiply " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing overflow.\n");
		}
		return numerical((n1 * n2));
	}, _val, rhs._val);
	return *this;
}

Numerical		&Numerical::operator/=(const Numerical &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		if (divisionExceedsLimits(n1, n2)) {
			throw std::overflow_error("Cannot divide " + std::to_string(n1) + 
			" and " + std::to_string(n2) + " without causing overflow.\n");
		}
		return numerical((n1 / n2));
	}, _val, rhs._val);
	return *this;
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
	// return std::visit([](auto n1, auto n2) {
	// 	return Numerical((n1 + n2));
	// }, lhs.getVal(), rhs.getVal());
}

Numerical	operator-(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp -= rhs;
	// return std::visit([](auto n1, auto n2) {
	// 	return Numerical((n1 - n2));
	// }, lhs.getVal(), rhs.getVal());
}

Numerical	operator*(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp *= rhs;
	// return std::visit([](auto n1, auto n2) {
	// 	return Numerical((n1 * n2));
	// }, lhs.getVal(), rhs.getVal());
}

Numerical	operator/(const Numerical &lhs, const Numerical &rhs) {
	Numerical tmp = lhs;
	return tmp /= rhs;
	// return std::visit([](auto n1, auto n2) {
	// 	return Numerical((n1 / n2));
	// }, lhs.getVal(), rhs.getVal());
}


// Numerical	simplifyRadical(const Numerical &n) {

// }

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
