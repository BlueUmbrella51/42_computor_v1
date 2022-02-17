#include "../headers/token.hpp"

// Parser::Parser() {
// 	_side = left;
// 	_var = '0';
// 	isExpected = NULL;
// }

// void	Parser::setVar(char c) {
// 	_var = c;
// }

// char	Parser::getVar() {
// 	return _var;
// }

// bool	Parser::varIsSet() {
// 	return (_var != '0');
// }

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

Tokens::Tokens() {
	_variable = std::nullopt;
	_tokens = {};
}

Tokens::~Tokens() {

}

std::list<Token>	Tokens::getTokens() {
	return _tokens;
}

void	Tokens::print() {
	std::list<Token>::iterator it;
	for (it = _tokens.begin(); it != _tokens.end(); ++it) {
    	it->print();
	}
}

// Token	*find_token(std::list<Token> &tokens, int degree) {
// 	for( std::list<Token>::iterator iter= tokens.begin(); iter != tokens.end(); iter++ )
// 	{
// 		if (iter->getDegree() == degree) {
// 			return iter;
// 		}
// 	}
// 	return NULL;
// }

Token	*Tokens::has_degree(int degree) {
	// auto iter = std::find_if(_tokens.begin(),
    //                      _tokens.end(),
    //                      [degree](Token s) -> bool { return (s.getDegree() == degree); });
	// if (iter != _tokens.end()) {
	// 	return &iter;
	// }
	// else {
	// 	return nullptr;
	// }
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
	printf("%p %f %i\n", (void *)found, coeff, degree);
	if (found == NULL) {
		printf("Not found\n");
		_tokens.push_back(Token(coeff, degree));
	}
	else {
		found->setCoeff(found->getCoeff() + coeff);
	}
}

void	Tokens::setVar(char var) {
	_variable = var;
}

std::optional<char>	Tokens::getVar() {
	return (_variable);
}

void	Tokens::sort() {
	_tokens.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}

// void	Tokens::combine() {
// 	/* 
// 	Combine all elements sharing a degree into a new list
// 	*/
// 	std::list<Token> combined = {};
// 	std::list<Token>::iterator curr = _tokens.begin();
// 	int degree = curr->getDegree();
// 	float total = curr->getCoeff();
// 	// std::cout << "Degree: " << degree << std::endl;
// 	// std::cout << "Coeff: " << total << std::endl;
// 	while (curr != _tokens.end()) {
// 		std::cout << "Degree: " << degree << std::endl;
// 		std::cout << "Coeff: " << total << std::endl;
// 		if (curr->getDegree() == degree) {
// 			total += curr->getCoeff();
// 		}
// 		else {
// 			// char sign = total > 0 ? '+' : '-';
// 			combined.push_back(Token(total, degree));
// 			degree = curr->getDegree();
// 			total = curr->getCoeff();
// 		}
// 		curr++;
// 	}
// 	std::list<Token>::iterator it;
// 	std::cout << "AFTER COMBINE" << std::endl;
// 	for (it = combined.begin(); it != combined.end(); ++it) {
//     	it->print();
// 	}
// 	_tokens = combined;
// }