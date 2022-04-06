#include "Rational.h"

Rational::Rational() :
_val{real(0)} {}

Rational::Rational(real n) :
_val{n} {}

Rational::Rational(Fraction n) :
_val{real(n)} {}

Rational::Rational(const Rational &rhs) :
_val{rhs._val} {

}

bool	Rational::isIntegral() {
	return (std::holds_alternative<int>(_val)
	|| std::holds_alternative<long>(_val)
	|| std::holds_alternative<long long>(_val));
}

bool	Rational::isFloating() {
	return (std::holds_alternative<float>(_val)
	|| std::holds_alternative<double>(_val)
	|| std::holds_alternative<long double>(_val));
}

bool	Rational::isFraction() {
	return std::holds_alternative<Fraction>(_val);
}

long double	Rational::toFloating() {
	return std::visit([](auto &arg) {
		try {
			return (long double)arg;
		}
		catch (std::overflow_error &e) {
			std::cout << e.what();
			throw e;
		}
	}, _val);
}

// long double		Rational::getFloat() {
// 	return std::visit([](auto &arg) {
// 		return (long double)arg;
// 	}, _val);
// }

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Rational::operator	std::string () const {
	return std::visit(overloaded {
		[](Fraction arg) { return std::string(arg); },
		[](auto arg) { return std::to_string(arg); }
	}, _val);
}

// Rational::operator long double () const {
// 	return std::visit([](auto &arg) {
// 		return (long double)arg;
// 	}, _val);
// }

real	Rational::getVal() const {
	return _val;
}

Rational	&Rational::operator=(const Rational &rhs) {
	if (this != &rhs) {
		this->_val = rhs._val;
	}
	return *this;
}

Rational		Rational::operator-() {
	return std::visit([](auto &arg){
		return Rational(-arg);
	}, _val);
}

Rational	&Rational::operator+=(const Rational &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 + n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator-=(const Rational &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 - n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator/=(const Rational &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 / n2);
	}, _val, rhs._val);
	return *this;
}

Rational	&Rational::operator*=(const Rational &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 * n2);
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

Rational		operator+(const Rational &a, const Rational &b) {
	return std::visit([](auto &n1, auto &n2){
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

std::ostream    	&operator<<(std::ostream &os, const Rational &x) {
	std::visit([&os](auto &n){
		os << n;
	}, x._val);
	return os;
}

Rational				getGcd(const Rational &a, const Rational &b) {
	return std::visit([] (auto &a, auto &b) {
		return Rational(real(getGcd(a, b)));
	}, a._val, b._val);
}

std::pair<Rational, Rational>			simplify_radical(const Rational &r, int degree) {
	return std::visit([&degree] (auto &a) {
		try {
			auto [whole, radical] = simplify_radical(a, degree);
			std:: cout << "Check\n";
			return std::make_pair(Rational(whole), Rational(radical));
		}
		catch (std::overflow_error &e) {
			std::cout << e.what();
			throw e;
		}
	}, r._val);
}

Rational				abs(const Rational &r) {
	auto n = r._val;
	if (std::holds_alternative<Fraction>(n)) {
		return Rational(abs(std::get<Fraction>(n)));
	}
	else if (std::holds_alternative<int>(n) || (std::holds_alternative<long>(n))
	|| (std::holds_alternative<long long>(n))) {
		return Rational(std::abs(std::get<long long>(n)));
	}
	else {
		return Rational(std::abs(std::get<long double>(n)));
	}
}