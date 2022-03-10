#include "Token.h"

Token::~Token() {

}

Token::Token() {

}

// template <typename T>
Token::Token(coeffOpts coeff, int degree) {
	_coeff = coeff;
	_degree = degree;
}

void	Token::print() {
	std::cout << "TOKEN" << std::endl
	<< "Coeff: ";
	std::visit([] (auto&& e) {
		std::cout << e;
	}, _coeff);
	std::cout << std::endl
	<< "Degree: " << _degree << std::endl;
	// std::cout << std::endl;
}

int		Token::getDegree() const {
	return _degree;
}

double	Token::getCoeff() const {
	// return _coeff;
	return 1;
}

// void	Token::setCoeff(double n) {
// 	_coeff = n;
// }

bool	Token::operator==(const Token &x) {
	return (getCoeff() == x.getCoeff() && getDegree() == x.getDegree());
}
