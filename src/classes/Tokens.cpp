#include "headers/Tokens.hpp"
#include <list>

Tokens::Tokens() : _side(Tokens::operationSide::left) {
	_tokens = {};
	_highest_degree = 0;
}

Tokens::~Tokens() {

}

std::list<Token>	Tokens::getTokens() {
	return _tokens;
}

Tokens::operationSide	Tokens::getSide() {
	return _side;
}

int		Tokens::getHighestDegree() {
	return _highest_degree;
}

void	Tokens::setHighestDegree(int n) {
	_highest_degree = n;
}

void	Tokens::print() {
	std::list<Token>::iterator it;
	printf("Highest degree: %d\n", _highest_degree);
	for (it = _tokens.begin(); it != _tokens.end(); ++it) {
    	it->print();
	}
}

Token	*Tokens::has_degree(int degree) {
	for (std::list<Token>::iterator iter= _tokens.begin(); iter != _tokens.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return &*iter;
		}
	}
	return NULL;
}

void	Tokens::add(double coeff, int degree) {
	Token *found = has_degree(degree);
	if (degree > _highest_degree) {
		_highest_degree = degree;
	}
	// printf("%p %f %i\n", (void *)found, coeff, degree);
	if (found == NULL) {
		// printf("Not found\n");
		_tokens.push_back(Token(coeff, degree));
	}
	else {
		found->setCoeff(found->getCoeff() + coeff);
	}
}

void	Tokens::sort() {
	_tokens.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}
