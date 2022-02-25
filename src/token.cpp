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

// Equation::Equation() {
// 	_variable = std::nullopt;
// 	_Equation = {};
// 	_highest_degree = 0;
// }

// Equation::~Equation() {
// }

// std::list<Token>	Equation::getEquation() {
// 	return _Equation;
// }

// int		Equation::getHighestDegree() {
// 	return _highest_degree;
// }

// void	Equation::setHighestDegree(int n) {
// 	_highest_degree = n;
// }

// void	Equation::print() {
// 	std::list<Token>::iterator it;
// 	printf("Highest degree: %d\n", _highest_degree);
// 	for (it = _Equation.begin(); it != _Equation.end(); ++it) {
//     	it->print();
// 	}
// }

// Token	*Equation::has_degree(int degree) {
// 	for (std::list<Token>::iterator iter= _Equation.begin(); iter != _Equation.end(); iter++)
// 	{
// 		if (iter->getDegree() == degree) {
// 			return &*iter;
// 		}
// 	}
// 	return NULL;
// }

// void	Equation::add(double coeff, int degree) {
// 	Token *found = has_degree(degree);
// 	if (degree > _highest_degree) {
// 		_highest_degree = degree;
// 	}
// 	// printf("%p %f %i\n", (void *)found, coeff, degree);
// 	if (found == NULL) {
// 		// printf("Not found\n");
// 		_Equation.push_back(Token(coeff, degree));
// 	}
// 	else {
// 		found->setCoeff(found->getCoeff() + coeff);
// 	}
// }

// void	Equation::setVar(char var) {
// 	_variable = var;
// }

// std::optional<char>	Equation::getVar() {
// 	return (_variable);
// }

// void	Equation::sort() {
// 	_Equation.sort([](const Token & t1, const Token & t2) {
// 		return (t1.getDegree() > t2.getDegree());
// 	});
// }
