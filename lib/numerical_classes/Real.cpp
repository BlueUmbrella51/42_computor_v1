#include "Real.h"

Real::Real(real n) :
_val{n} {
}

Real::Real(Rational n) :
_val{real(n)} {
}

Real::Real(const Real &rhs) :
_val{rhs._val} {

}

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Real::operator	std::string () const {
	return std::visit(overloaded {
		[](Rational arg) { return std::string(arg); },
		[](auto arg) { return std::to_string(arg); }
	}, _val);
}

real	Real::getVal() const {
	return _val;
}

Real	&Real::operator=(const Real &rhs) {
	if (this != &rhs) {
		this->_val = rhs._val;
	}
	return *this;
}

Real		Real::operator-() {
	return std::visit([](auto &arg){
		return Real(-arg);
	}, _val);
}

Real	&Real::operator+=(const Real &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 + n2);
	}, _val, rhs._val);
	return *this;
}

Real	&Real::operator-=(const Real &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 - n2);
	}, _val, rhs._val);
	return *this;
}

Real	&Real::operator/=(const Real &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 / n2);
	}, _val, rhs._val);
	return *this;
}

Real	&Real::operator*=(const Real &rhs) {
	_val = std::visit([](auto &n1, auto &n2) {
		return real(n1 * n2);
	}, _val, rhs._val);
	return *this;
}

bool	operator==(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 == n2);
	}, lhs._val, rhs._val);
}

bool	operator!=(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 != n2);
	}, lhs._val, rhs._val);
}

bool	operator>(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 > n2);
	}, lhs._val, rhs._val);
}

bool	operator>=(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 >= n2);
	}, lhs._val, rhs._val);
}

bool	operator<(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 < n2);
	}, lhs._val, rhs._val);
}

bool	operator<=(const Real &lhs, const Real &rhs) {
	return std::visit([](auto &n1, auto &n2){
		return (n1 <= n2);
	}, lhs._val, rhs._val);
}

Real		operator+(const Real &a, const Real &b) {
	return std::visit([](auto &n1, auto &n2){
		return Real(n1 + n2);
	}, a._val, b._val);
}

Real		operator-(const Real &a, const Real &b) {
	return std::visit([](auto &n1, auto &n2){
		return Real(n1 - n2);
	}, a._val, b._val);
}

Real		operator*(const Real &a, const Real &b) {
	return std::visit([](auto &n1, auto &n2){
		return Real(n1 * n2);
	}, a._val, b._val);
}

Real		operator/(const Real &a, const Real &b) {
	return std::visit([](auto &n1, auto &n2){
		return Real(n1 / n2);
	}, a._val, b._val);
}

std::ostream    	&operator<<(std::ostream &os, const Real &x) {
	std::visit([&os](auto &n){
		os << n;
	}, x._val);
	return os;
}

Real				getGcd(const Real &a, const Real &b) {
	return std::visit([] (auto &a, auto &b) {
		return Real(real(getGcd(a, b)));
	}, a._val, b._val);
}
