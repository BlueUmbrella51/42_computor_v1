#include "headers/Token.hpp"

Token::~Token() {

}

Token::Token(float coeff, int degree) {
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

void	Token::setCoeff(double c) {
	_coeff = c;
}
