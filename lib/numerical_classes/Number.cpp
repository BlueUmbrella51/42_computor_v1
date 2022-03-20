#include "Number.h"

Number::Number(number n) :
_val(n) {
}

Number::Number(Rational n) :
_val(number(n)) {
}

Number::Number(const Number &rhs) :
_val{rhs._val} {

}

Number	&Number::operator=(const Number &rhs) {
	if (this != &rhs) {
		this->_val = rhs._val;
	}
	return *this;
}

Number		operator+(const Number &a, const Number &b) {
	return std::visit([](auto &n1, auto &n2){
		return Number(number(n1 + n2));
	}, a._val, b._val);
}

Number		operator*(const Number &a, const Number &b) {
	return std::visit([](auto &n1, auto &n2){
		return Number(number(n1 * n2));
	}, a._val, b._val);
}

Number		operator/(const Number &a, const Number &b) {
	return std::visit([](auto &n1, auto &n2){
		return Number(number(n1 / n2));
	}, a._val, b._val);
}

// number		operator-(const  number &a, const  number &b) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return number((n1 - n2));
// 	}, a, b);
// }

std::ostream    	&operator<<(std::ostream &os, const Number &x) {
	std::visit([&os](auto &n){
		os << n;
	}, x._val);
	return os;
}


Number				getGcd(const Number &a, const Number &b) {
	return std::visit([] (auto &a, auto &b) {
		return Number(number(getGcd(a, b)));
	}, a._val, b._val);
}

// HERE
// #include "Number.h"

// Number::Number(number n) {
// 	_val = number;
// }

// Number::Number(long long n) {
// 	_val = Rational(n, 1);
// }

// Number::~Number() {

// }

// Number			&Number::operator*=(const Number &n) {
// 	std::visit([](auto &n1, auto &n2){
// 		n1 *= n2;
// 	}, (*this)._val, n._val);
// 	return *this;
// }

// Number			&Number::operator/=(Number &n) {
// 	std::visit([](auto &n1, auto &n2){
// 		n1 /= n2;
// 	}, (*this)._val, n._val);
// 	return *this;
// }
// Number			&Number::operator+=(Number &n) {
// 	std::visit([](auto &n1, auto &n2){
// 		n1 += n2;
// 	}, (*this)._val, n._val);
// 	return *this;
// }

// Number			&Number::operator-=(Number &n) {
// 	std::visit([](auto &n1, auto &n2){
// 		n1 -= n2;
// 	}, (*this)._val, n._val);
// 	return *this;
// }

// Number		operator*(Number &a, Number &b) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return Number((n1 * n2));
// 	}, a._val, b._val);
// }

// Number		operator/(Number &a, Number &b) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return Number((n1 / n2));
// 	}, a._val, b._val);
// }

// Number		operator+(Number &a, Number &b) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return Number((n1 + n2));
// 	}, a._val, b._val);
// }

// Number		operator-(Number &a, Number &b) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return Number((n1 - n2));
// 	}, a._val, b._val);
// }

// std::ostream    &operator<<(std::ostream &os, const Number &x) {
// 	std::visit([](auto &n){
// 		os << n;
// 	}, x._val);
// 	return os;
// }

// bool            operator==(const Number &lhs, const Number &rhs) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return (n1 == n2)
// 	}, lhs._val, rhs._val);
// }

// Number			getGcd(Number &lhs, Number &rhs) {
// 	return std::visit([](auto &n1, auto &n2){
// 		return (Number(getGcd(n1, n2)));
// 	}, lhs._val, rhs._val);
// }



// template	long long getGcd<int, int>(int n, int m);
// template	long long getGcd<int, long>(int n, long m);
// template	long long getGcd<int, long long>(int n, long long m);
// template	long long getGcd<long, int>(long n, int m);
// template	long long getGcd<long, long>(long n, long m);
// template	long long getGcd<long, long long>(long n, long long m);
// template	long long getGcd<long long, long>(long long n, long m);
// template	long long getGcd<long long, int>(long long n, int m);
// template	long long getGcd<long long, long long>(long long n, long long m);

// template	long long getGcd<long, float>(long n, float m);
// template	long long getGcd<float, long>(float n, long m);
// template	long long getGcd<long, double>(long n, double m);
// template	long long getGcd<double, long>(double n, long m);
// template	long long getGcd<long, long double>(long n, long double m);
// template	long long getGcd<long double, long>(long double n, long m);
// template	long long getGcd<long, float>(long n, float m);
// template	long long getGcd<float, long>(float n, long m);
// template	long long getGcd<long, double>(long n, double m);
// template	long long getGcd<double, long>(double n, long m);
// template	long long getGcd<long, long double>(long n, long double m);
// template	long long getGcd<long double, long>(long double n, long m);

// template	long long getGcd<long long, float>(long long n, float m);
// template	long long getGcd<float, long long>(float n, long long m);
// template	long long getGcd<long long, double>(long long n, double m);
// template	long long getGcd<double, long long>(double n, long long m);
// template	long long getGcd<long long, long double>(long long n, long double m);
// template	long long getGcd<long double, long long>(long double n, long long m);
// template	long long getGcd<long long, float>(long long n, float m);
// template	long long getGcd<float, long long>(float n, long long m);
// template	long long getGcd<long long int, double>(long long n, double m);
// template	long long getGcd<double, long long>(double n, long long m);
// template	long long getGcd<long long, long double>(long long n, long double m);
// template	long long getGcd<long double, long long>(long double n, long long m);