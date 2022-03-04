#include "Token.h"

Token::~Token() {

}

Token::Token(double coeff, int degree) {
	_coeff = coeff;
	_degree = degree;
}

void	Token::print() {
	std::cout << "TOKEN" << std::endl
	<< "Coefficient: " << _coeff << std::endl
	<< "Degree: " << _degree << std::endl;
	std::cout << std::endl;
}

int		Token::getDegree() const {
	return _degree;
}

double	Token::getCoeff() const {
	return _coeff;
}

void	Token::setCoeff(double n) {
	_coeff = n;
}

bool	Token::operator==(const Token &x) {
	return (getCoeff() == x.getCoeff() && getDegree() == x.getDegree());
}
