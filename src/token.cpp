#include "../headers/token.hpp"

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

float	Token::getCoeff() const {
	return _coeff;
}

Tokens::Tokens(char var) {
	_variable = var;
	_tokens = {};
}

Tokens::~Tokens() {

}

void	Tokens::print() {
	std::list<Token>::iterator it;
	for (it = _tokens.begin(); it != _tokens.end(); ++it) {
    	it->print();
	}
}

void	Tokens::add(Token t) {
	_tokens.push_back(t);
}

void	Tokens::setVar(char var) {
	_variable = var;
}

void	Tokens::sort() {
	_tokens.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}

void	Tokens::combine() {
	/* 
	Combine all elements sharing a degree into a new list
	*/
	std::list<Token> combined = {};
	std::list<Token>::iterator curr = _tokens.begin();
	int degree = curr->getDegree();
	float total = curr->getCoeff();
	// std::cout << "Degree: " << degree << std::endl;
	// std::cout << "Coeff: " << total << std::endl;
	while (curr != _tokens.end()) {
		std::cout << "Degree: " << degree << std::endl;
		std::cout << "Coeff: " << total << std::endl;
		if (curr->getDegree() == degree) {
			total += curr->getCoeff();
		}
		else {
			// char sign = total > 0 ? '+' : '-';
			combined.push_back(Token(total, degree));
			degree = curr->getDegree();
			total = curr->getCoeff();
		}
		curr++;
	}
	std::list<Token>::iterator it;
	std::cout << "AFTER COMBINE" << std::endl;
	for (it = combined.begin(); it != combined.end(); ++it) {
    	it->print();
	}
	_tokens = combined;
}