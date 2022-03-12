#include "Token.h"

Token::~Token() {

}

// Token::Token() {

// }

// template <typename T>
Token::Token(coeffOpts coeff, int degree) {
	_coeff = coeff;
	_degree = degree;
}

void	Token::print() const {
	std::cout << "TOKEN" << std::endl
	<< "Coeff: ";
	std::visit([] (auto&& e) {
		std::cout << e;
	}, _coeff);
	std::cout << std::endl
	<< "Degree: " << _degree << "\n\n";
	// std::cout << std::endl;
}

int		Token::getDegree() const {
	return _degree;
}

Token::coeffOpts	Token::getCoeff() const {
	return _coeff;
	// return 1;
}

// void	Token::setCoeff(double n) {
// 	_coeff = n;
// }

bool	Token::operator==(const Token &x) {
	return (getCoeff() == x.getCoeff() && getDegree() == x.getDegree());
}

Token		operator*(const Token &t, long long n) {
	return std::visit([t, n] (auto &&arg) {
		return Token(arg * n, t.getDegree());
	}, t.getCoeff());
}

Token		operator+(const Token &lhs, Token &rhs) {
	return std::visit([lhs] (auto &&arg1, auto &&arg2) {
		return Token(arg1 + arg2, lhs.getDegree());
	}, lhs.getCoeff(), rhs.getCoeff());
}

struct opts {
	void operator() (Rational, Rational) { std::cout <<"Rational Rational"; }
	void operator() (Rational, long double) { std::cout <<"Rational, long double"; }
	void operator() (long double, Rational) { std::cout <<"Rational, long double"; }
	void operator() (Rational, long long) { std::cout <<"Rational, long long"; }
	void operator() (long long, Rational) { std::cout <<"Rational, long long"; }
	void operator() (long long, long long) { std::cout <<"long long, long long"; }
	void operator() (long long, long double) { std::cout <<"long long, long double"; }
	void operator() (long double, long long) { std::cout <<"long double, long long"; }
	void operator() (long double, long double) { std::cout <<"long double, long double";}
};

Token::coeffOpts	getGcd(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs) {
	// printf("GET GCD\n");
	std::visit(opts(), lhs, rhs);
	Token::coeffOpts res = std::visit([] (auto &&arg1, auto &&arg2) {
		return Token::coeffOpts(getGcd(arg1, arg2));
	}, lhs, rhs);
	return res;
	// return 1LL;
}
