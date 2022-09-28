#include "Token.h"

Token::Token(): _coeff(Rational(0)), _degree(0), _isConst(true){}

Token::Token(Rational coeff, long degree, bool isConst) :
_coeff{coeff}, _degree{degree}, _isConst(isConst) {}

Token::operator std::string() const {
	/* Coefficient and degree to string */
	std::string res = "";
	auto 		coeff = _coeff;

	if (coeff < 0) {
		res += "-";
		coeff = abs(coeff);
	}
	if (coeff != 1 || (coeff == 1 && _isConst)) {
		/* Do not print a 1 if an 'X' is going to follow it directly */
		res += std::string(coeff);
	}
	if (!_isConst) {
		if (coeff != 0) {
			res += "X";
			if (_degree == 2) {
				res += PWR_TWO;
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

bool		Token::isConstant() const {
	return _isConst;
}

void		Token::setCoeff(Rational coeff) {
	_coeff = coeff;
}

bool			operator==(const Token &lhs, const Token &rhs) {
	return (lhs.getDegree() == rhs.getDegree() && lhs.getCoeff() == rhs.getCoeff());
}