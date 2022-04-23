#include "Rational.h"

Rational::Rational() :
_val{real(Numerical(0))} {}

Rational::Rational(Numerical n) :
_val{real(n)} {}

Rational::Rational(Fraction n) :
_val{real(n)} {}

Rational::Rational(const Rational &rhs) :
_val{rhs._val} {}

bool	Rational::isIntegral() const {
	if (std::holds_alternative<Numerical>(_val)) {
		auto n = std::get<Numerical>(_val);
		return n.isIntegral();
	}
	else {
		return false;
	}
}

bool	Rational::isFloating() const {
	if (std::holds_alternative<Numerical>(_val)) {
		auto n = std::get<Numerical>(_val);
		std::cout << n.isFloating();
		return n.isFloating();
	}
	else {
		return false;
	}
}

bool	Rational::isFraction() const {
	return std::holds_alternative<Fraction>(_val);
}

Rational::operator long double () const {
	return std::visit([](auto &arg) {
		return (long double)arg;
	}, _val);
}

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Rational::operator	std::string () const {
	return std::visit(overloaded {
		[](Fraction arg) { return std::string(arg); },
		[](Numerical arg) { return std::string(arg); }
	}, _val);
}

Rational::operator long long() const {
	return std::visit(overloaded {
		[](Fraction arg) { return (long long)arg; },
		[](Numerical arg) { return (long long)arg; }
	}, _val);
}

Rational		trunc(const Rational &r) {
	return std::visit(overloaded {
		[](Fraction arg) { return Rational(Fraction(arg.getWhole())); },
		[](Numerical arg) { return Rational(trunc(arg)); }
	}, r._val);
}

real	Rational::getVal() const {
	return _val;
}

Rational	&Rational::operator=(const Rational &rhs) {
	if (this != &rhs) {
		_val = rhs._val;
	}
	return *this;
}

Rational		Rational::operator-() {
	return std::visit([](auto &arg){
		return Rational(-arg);
	}, _val);
}

Rational	&Rational::operator+=(const Rational &rhs) {
	*this = std::visit([](auto &n1, auto &n2) {
		return Rational(n1 + n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator-=(const Rational &rhs) {
	*this = std::visit([](auto &n1, auto &n2) {
		return Rational(n1 - n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator/=(const Rational &rhs) {
	*this = std::visit([](auto &n1, auto &n2) {
		return Rational(n1 / n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator*=(const Rational &rhs) {
	*this = std::visit([](auto &n1, auto &n2) {
		return Rational(n1 * n2);
	}, _val, rhs._val);
	return *this;
}

bool	operator==(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 == n2);
	}, lhs._val, rhs._val);
}

bool	operator!=(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 != n2);
	}, lhs._val, rhs._val);
}

bool	operator>(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 > n2);
	}, lhs._val, rhs._val);
}

bool	operator>=(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 >= n2);
	}, lhs._val, rhs._val);
}

bool	operator<(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 < n2);
	}, lhs._val, rhs._val);
}

bool	operator<=(const Rational &lhs, const Rational &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 <= n2);
	}, lhs._val, rhs._val);
}

bool		operator==(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return (n == rhs);
	}, lhs.getVal());
}

bool		operator==(const Fraction &lhs, const Numerical &rhs) {
	return (rhs == lhs);
}

bool		operator!=(const Numerical &lhs, const Fraction &rhs) {
	return !(lhs == rhs);
}

bool		operator!=(const Fraction &lhs, const Numerical &rhs) {
	return !(lhs == rhs);
}

bool		operator<(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return (n < rhs);
	}, lhs.getVal());
}

bool		operator<(const Fraction &lhs, const Numerical &rhs) {
	return !(rhs < lhs || lhs == rhs);
}

bool		operator<=(const Numerical &lhs, const Fraction &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator<=(const Fraction &lhs, const Numerical &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator>(const Numerical &lhs, const Fraction &rhs) {
	return !(lhs <= rhs);
}

bool		operator>(const Fraction &lhs, const Numerical &rhs) {
	return !(lhs <= rhs);
}

bool		operator>=(const Numerical &lhs, const Fraction &rhs) {
	return !(lhs < rhs);
}

bool		operator>=(const Fraction &lhs, const Numerical &rhs) {
	return !(lhs < rhs);
}

Rational		operator+(const Rational &a, const Rational &b) {
	return std::visit([](auto &n1, auto &n2) {
		return Rational(n1 + n2);
	}, a._val, b._val);
}

Rational		operator-(const Rational &a, const Rational &b) {
	return std::visit([](auto &n1, auto &n2){
		return Rational(n1 - n2);
	}, a._val, b._val);
}

Rational		operator*(const Rational &a, const Rational &b) {
	return std::visit([](auto &n1, auto &n2){
		return Rational(n1 * n2);
	}, a._val, b._val);
}

Rational		operator/(const Rational &a, const Rational &b) {
	return std::visit([](auto &n1, auto &n2){
		return Rational(n1 / n2);
	}, a._val, b._val);
}

Rational	operator+(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return Rational((n + rhs));
	}, lhs.getVal());
}

Rational	operator+(const Fraction &lhs, const Numerical &rhs) {
	return (rhs + lhs);
}

Rational	operator-(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return Rational((n - rhs));
	}, lhs.getVal());
}

Rational	operator-(const Fraction &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Rational((lhs - n));
	}, rhs.getVal());
}

Rational	operator*(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return Rational((n * rhs));
	}, lhs.getVal());
}

Rational	operator*(const Fraction &lhs, const Numerical &rhs) {
	return (rhs * lhs);
}

Rational	operator/(const Numerical &lhs, const Fraction &rhs) {
	return std::visit([=](auto n) {
		return Rational((n / rhs));
	}, lhs.getVal());
}

Rational	operator/(const Fraction &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Rational((lhs / n));
	}, rhs.getVal());
}

std::ostream    	&operator<<(std::ostream &os, const Rational &x) {
	os << (std::string)x;
	return os;
}

Rational				getGcd(const Rational &a, const Rational &b) {
	return std::visit([=](auto n1, auto n2) {
		return Rational(getGcd(n1, n2));
	}, a.getVal(), b.getVal());
}

Rational				abs(const Rational &r) {
	return std::visit([=](auto n) {
		return Rational(abs(n));
	}, r.getVal());
}


bool		operator==(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return (n == rhs);
	}, lhs.getVal());
}

bool		operator==(const Rational &lhs, const Numerical &rhs) {
	return (rhs == lhs);
}

bool		operator!=(const Numerical &lhs, const Rational &rhs) {
	return !(lhs == rhs);
}

bool		operator!=(const Rational &lhs, const Numerical &rhs) {
	return !(lhs == rhs);
}

bool		operator<(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return (n < rhs);
	}, lhs.getVal());
}

bool		operator<(const Rational &lhs, const Numerical &rhs) {
	return !(rhs < lhs || lhs == rhs);
}

bool		operator<=(const Numerical &lhs, const Rational &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator<=(const Rational &lhs, const Numerical &rhs) {
	return (lhs < rhs || lhs == rhs);
}

bool		operator>(const Numerical &lhs, const Rational &rhs) {
	return !(lhs <= rhs);
}

bool		operator>(const Rational &lhs, const Numerical &rhs) {
	return !(lhs <= rhs);
}

bool		operator>=(const Numerical &lhs, const Rational &rhs) {
	return !(lhs < rhs);
}

bool		operator>=(const Rational &lhs, const Numerical &rhs) {
	return !(lhs < rhs);
}

Rational	operator+(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return Rational((n + rhs));
	}, lhs.getVal());
}

Rational	operator+(const Rational &lhs, const Numerical &rhs) {
	return (rhs + lhs);
}

Rational	operator-(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return Rational((n - rhs));
	}, lhs.getVal());
}

Rational	operator-(const Rational &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Rational((lhs - n));
	}, rhs.getVal());
}

Rational	operator*(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return Rational((n * rhs));
	}, lhs.getVal());
}
Rational	operator*(const Rational &lhs, const Numerical &rhs) {
	return (rhs * lhs);
}

Rational	operator/(const Numerical &lhs, const Rational &rhs) {
	return std::visit([=](auto n) {
		return Rational((n / rhs));
	}, lhs.getVal());
}

Rational	operator/(const Rational &lhs, const Numerical &rhs) {
	return std::visit([=](auto n) {
		return Rational((lhs / n));
	}, rhs.getVal());
}
