#include "Token.h"

Token::Token(Rational coeff, long degree) :
_coeff{coeff}, _degree{degree}{
	
}

Token::operator std::string() const {
	/* Coefficient and degree to string */
	std::string res = "";

	res += std::string(_coeff);
	if (_coeff != 0) {
		if (_degree != 0) {
			res += "X";
			if (_degree == 2) {
				res += "²";
			}
			else if (_degree != 1) {
				res += "^" + std::to_string(_degree);
			}
		}
	}
	return res;
}

std::ostream &operator<<(std::ostream &os, const Token &r) {
	os << (std::string)r;
	return os;
}

long		Token::getDegree() const{
	return _degree;
}

Rational		Token::getCoeff() const {
	return _coeff;
}

void		Token::setCoeff(Rational coeff) {
	_coeff = coeff;
}

bool			operator==(const Token &lhs, const Token &rhs) {
	return (lhs.getDegree() == rhs.getDegree() && lhs.getCoeff() == rhs.getCoeff());
}