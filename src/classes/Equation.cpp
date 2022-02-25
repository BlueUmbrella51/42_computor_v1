#include "headers/Equation.hpp"
#include <list>

Equation::Equation() : _side(Equation::operationSide::left) {
	_tokens = {};
	_highest_degree = 0;
}

Equation::~Equation() {

}

std::list<Token>	&Equation::getTokens() {
	return _tokens;
}

Equation::operationSide	Equation::getSide() {
	return _side;
}

void	Equation::setSide(Equation::operationSide s) {
	_side = s;
}

int		Equation::getHighestDegree() {
	return _highest_degree;
}

void	Equation::setHighestDegree(int n) {
	_highest_degree = n;
}

void	Equation::print() {
	// std::list<Token>::iterator it;
	printf("EQUATION:\nHighest degree: %i\n\n", _highest_degree);
	for (std::list<Token>::iterator it = _tokens.begin(); it != _tokens.end(); ++it) {
    	it->print();
	}
}

Token	*Equation::findTokenByDegree(int degree) {
	for (std::list<Token>::iterator iter = _tokens.begin(); iter != _tokens.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return &*iter;
		}
	}
	return NULL;
}

void	Equation::add(double coeff, int degree) {
    // 0 coefficients means zero, so adding is meaningless
	if (coeff == 0) {
		return ;
	}
	Token *found = findTokenByDegree(degree);
	if (degree > _highest_degree) {
		_highest_degree = degree;
	}
	if (found == NULL) {
		_tokens.push_back(Token(coeff, degree));
	}
	else {
		found->setCoeff(found->getCoeff() + coeff);
	}
}

double	Equation::findCoefficientOfDegree(int degree) {
	Token *found = findTokenByDegree(degree);
	if (found == NULL) {
		return 0.0;
	}
	return found->getCoeff();
}

void	Equation::sort() {
	_tokens.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}

void	Equation::simplify() {
	// TODO: make own gcd which takes doubles and Rationals etc
	// Divide everything by GCD if one can be found
	// std::list<Token>::iterator it = _tokens.begin();
	// long int result = (long int)it->getCoeff();
	// for (; it != _tokens.end(); it++) {
	// 	printf("HERE\n");
	// 	it->print();
	// 	result = std::gcd((long int)it->getCoeff(), result);
	// }
	// printf("GCD: %ld\n", result);
}
