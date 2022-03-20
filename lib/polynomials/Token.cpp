#include "Token.h"

Token::~Token() {

}

// Token::Token() {

// }

// template <typename T>
Token::Token(Number coeff, long degree) :
_coeff{coeff}, _degree{degree}{
	
}

std::ostream &operator<<(std::ostream &os, const Token &r) {
	os << r._coeff << r._degree;
	return os;
}

long		Token::getDegree() const{
	return _degree;
}

Number		Token::getCoeff() const {
	return _coeff;
	// return 1;
}

void		Token::setCoeff(Number coeff) {
	_coeff = coeff;
}

// bool	Token::operator==(const Token &x) {
// 	return (getCoeff() == x.getCoeff() && getDegree() == x.getDegree());
// }

// Token		operator*(const Token &t, long long n) {
// 	return std::visit([t, n] (auto &&arg) {
// 		return Token(arg * n, t.getDegree());
// 	}, t.getCoeff());
// }

// Token		operator+(const Token &lhs, Token &rhs) {
// 	return std::visit([lhs] (auto &&arg1, auto &&arg2) {
// 		return Token(arg1 + arg2, lhs.getDegree());
// 	}, lhs.getCoeff(), rhs.getCoeff());
// }

// Token::coeffOpts	getGcd(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs) {
// 	return std::visit([] (auto &&arg1, auto &&arg2) {
// 		return Token::coeffOpts(getGcd(arg1, arg2));
// 	}, lhs, rhs);
// }

// Token::coeffOpts		operator/(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs) {
// 	printf("COEFFOPTS /\n");
// 	return std::visit([] (auto &&arg1, auto &&arg2) {
// 		return Token::coeffOpts((arg1 / arg2));
// 	}, lhs, rhs);
// }
