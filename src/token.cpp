// #include "../headers/token.hpp"

// // Parser::Parser() {
// // 	_side = left;
// // 	_var = '0';
// // 	isExpected = NULL;
// // }

// // void	Parser::setVar(char c) {
// // 	_var = c;
// // }

// // char	Parser::getVar() {
// // 	return _var;
// // }

// // bool	Parser::varIsSet() {
// // 	return (_var != '0');
// // }

// Token::~Token() {

// }

// Token::Token(float coeff, int degree) {
// 	_coeff = coeff;
// 	_degree = degree;
// }

// void	Token::print() {
// 	std::cout << "TOKEN" << std::endl
// 	<< "Coefficient: " << _coeff << std::endl
// 	<< "Degree: " << _degree << std::endl;
// 	std::cout << std::endl;
// }

// int		Token::getDegree() const {
// 	return _degree;
// }

// double	Token::getCoeff() const {
// 	return _coeff;
// }

// void	Token::setCoeff(double c) {
// 	_coeff = c;
// }

// Tokens::Tokens() {
// 	_variable = std::nullopt;
// 	_tokens = {};
// 	_highest_degree = 0;
// }

// Tokens::~Tokens() {
// }

// std::list<Token>	Tokens::getTokens() {
// 	return _tokens;
// }

// int		Tokens::getHighestDegree() {
// 	return _highest_degree;
// }

// void	Tokens::setHighestDegree(int n) {
// 	_highest_degree = n;
// }

// void	Tokens::print() {
// 	std::list<Token>::iterator it;
// 	printf("Highest degree: %d\n", _highest_degree);
// 	for (it = _tokens.begin(); it != _tokens.end(); ++it) {
//     	it->print();
// 	}
// }

// Token	*Tokens::has_degree(int degree) {
// 	for (std::list<Token>::iterator iter= _tokens.begin(); iter != _tokens.end(); iter++)
// 	{
// 		if (iter->getDegree() == degree) {
// 			return &*iter;
// 		}
// 	}
// 	return NULL;
// }

// void	Tokens::add(double coeff, int degree) {
// 	Token *found = has_degree(degree);
// 	if (degree > _highest_degree) {
// 		_highest_degree = degree;
// 	}
// 	// printf("%p %f %i\n", (void *)found, coeff, degree);
// 	if (found == NULL) {
// 		// printf("Not found\n");
// 		_tokens.push_back(Token(coeff, degree));
// 	}
// 	else {
// 		found->setCoeff(found->getCoeff() + coeff);
// 	}
// }

// void	Tokens::setVar(char var) {
// 	_variable = var;
// }

// std::optional<char>	Tokens::getVar() {
// 	return (_variable);
// }

// void	Tokens::sort() {
// 	_tokens.sort([](const Token & t1, const Token & t2) {
// 		return (t1.getDegree() > t2.getDegree());
// 	});
// }
