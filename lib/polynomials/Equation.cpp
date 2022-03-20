#include "Equation.h"

Equation::Equation() : _side(Equation::operationSide::left) {
	_highest_degree = -1;
	_tokensLeft = {};
	_tokensRight = {};
}

Equation::~Equation() {

}

std::list<Token>	&Equation::getEquationLeft() {
	return _tokensLeft;
}

std::list<Token>	&Equation::getEquationRight() {
	return _tokensRight;
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

void	Equation::print() {
	printf("\n\n");
	printf("EQUATION\nhighest degree: %d\n", getHighestDegree());
	for (std::list<Token>::iterator it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
    	// it->print();
		std::cout << *it;
	}
	printf(" = ");
	for (std::list<Token>::iterator it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
    	std::cout << *it;
	}
	printf("\n\n");
}

Token	&Equation::findTokenByDegreeLeft(long int degree) {
	for (std::list<Token>::iterator iter = _tokensLeft.begin(); iter != _tokensLeft.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return *iter;
		}
	}
	throw std::invalid_argument("Token of degree not found.");
}

Token	&Equation::findTokenByDegreeRight(long int degree) {
	for (std::list<Token>::iterator iter = _tokensRight.begin(); iter != _tokensLeft.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return *iter;
		}
	}
	throw std::invalid_argument("Token of degree not found.");
}

// template <typename T>
void	Equation::add(Number coeff, int degree) {
	if (degree > _highest_degree) {
		_highest_degree = degree;
	}
	if (_side == operationSide::left) {
		_tokensLeft.push_back(Token(coeff, degree));
	}
	else {
		_tokensRight.push_back(Token(coeff, degree));
	}
}

// double	Equation::findCoefficientOfDegreeLeft(int degree) {
// 	Token *found = findTokenByDegreeLeft(degree);
// 	if (found == NULL) {
// 		return 0.0;
// 	}
// 	return found->getCoeff();
// }

// double	Equation::findCoefficientOfDegreeLeft()

void	Equation::sortLeft() {
	_tokensLeft.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}

// int		Equation::findHighestDegree() {
// 	int hd = -1;
// 	printf("Find highest degree\n");
// 	for (std::list<Token>::iterator iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
// 		if (iter->getDegree() > hd) {
// 			hd = iter->getDegree();
// 		}
// 	}
// 	printf("Highest: %d\n", hd);
// 	return (hd);
// }

void	Equation::combineTokensByDegreeLeft() {
	/* Only works on SORTED list */
	std::list<Token>::iterator it = _tokensLeft.begin();
	std::list<Token>::iterator curr = it;
	++it;
	while (it != _tokensLeft.end()) {
		if ((*it).getDegree() == (*curr).getDegree()) {
			try {
				(*curr).setCoeff((*curr).getCoeff() + (*it).getCoeff());
				it = _tokensLeft.erase(it);
			}
			catch (std::overflow_error &e) {
				throw e;
			}
		}
		else {
			curr = it;
			++it;
		}
	}
}

void	Equation::moveTokensLeft() {
	std::list<Token>::iterator iter = _tokensRight.begin();
	try {
		while (iter != _tokensRight.end())
		{
			_tokensLeft.push_back((*iter).getCoeff() * Number(number(-1)));
			iter = _tokensRight.erase(iter);
		}
	}
	catch (std::overflow_error &e) { throw (e); }
}

void	Equation::factorLeft() {
	// There can never be less than two tokens so this should be safe
	// TODO: wrap in try/ catch
	// TODO: make gcd negative if first token is negative
	std::list<Token>::iterator 	it = _tokensLeft.begin();
	Number						gcd = (*it).getCoeff();

	++it;
	// Token::coeffOpts n = Rational(1, 2);
	// Token::coeffOpts m = Rational(1, 4);
	// getGcd(n, m);
	while (it != _tokensLeft.end()) {
		auto curr = (*it).getCoeff();
		gcd = getGcd(curr, gcd);
		it++;
	}
	it = _tokensLeft.begin();
	for (std::list<Token>::iterator i = _tokensLeft.begin(); i != _tokensLeft.end(); ++i) {
		(*i).setCoeff((*i).getCoeff() / gcd);
	}
	// printf("GCD\n");
	// if (std::holds_alternative<Rational>(gcd)) {
	// 	std::cout << std::get<Rational>(gcd);
	// }
	// if (std::holds_alternative<long long>(gcd)) {
	// 	std::cout << std::get<long long>(gcd);
	// }
	// if (std::holds_alternative<long double>(gcd)) {
	// 	std::cout << std::get<long double>(gcd);
	// }
}

void	Equation::simplify() {
	/* 	Moves all tokens to left of equation
		Combines any tokens of same degree
	 */
	try {
		moveTokensLeft();
		printf("AFTER MOVE TOKENS LEFT\n");
		sortLeft();
		printf("AFTER SORT\n");
		print();
		combineTokensByDegreeLeft();
		printf("AFTER COMBINE\n");
		print();
		factorLeft();
		printf("AFTER FACTOR OUT GCD\n");
		print();
	}
	catch (std::overflow_error &e) { throw e; }
}
