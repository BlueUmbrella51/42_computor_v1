#include "Token.h"

Token::Token(Real coeff, long degree) :
_coeff{coeff}, _degree{degree}{
	
}

Token::operator std::string() const {
	/* Coefficient and degree to string */
	std::string res = "";

	res += std::string(_coeff);
	if (_degree != 0) {
		res += "X";
		if (_degree != 1) {
			res += "^" + std::to_string(_degree);
		}
	}
	return res;
}

std::ostream &operator<<(std::ostream &os, const Token &r) {
	auto coeff = r._coeff;
	auto degree = r._degree;

	os << coeff;
	if (degree != 0) {
		os << "X";
		if (degree != 1) {
			os << "^" << degree;
		}
	}
	return os;
}

long		Token::getDegree() const{
	return _degree;
}

Real		Token::getCoeff() const {
	return _coeff;
	// return 1;
}

void		Token::setCoeff(Real coeff) {
	_coeff = coeff;
}

bool			operator==(const Token &lhs, const Token &rhs) {
	return (lhs.getDegree() == rhs.getDegree() && lhs.getCoeff() == rhs.getCoeff());
}