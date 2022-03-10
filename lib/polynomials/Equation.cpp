#include "Equation.h"

Equation::Equation() : _side(Equation::operationSide::left) {
	_highest_degree = -1;
	// _tokensLeft = {};
	// _tokensRight = {};
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

// void	Equation::setHighestDegree(int n) {
// 	_highest_degree = n;
// }

// Rational		&Equation::getGcf() {
// 	return (_gcf);
// }

// void			Equation::setGcf(Rational &x) {
// 	_gcf = x;
// }

void	Equation::print() {
	printf("EQUATION\nhighest degree: %d\n", getHighestDegree());
	// printf("GCF:\n");
	// _gcf.print();
	for (std::list<Token>::iterator it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
    	it->print();
	}
	printf(" = ");
	for (std::list<Token>::iterator it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
    	it->print();
	}
}

Token	*Equation::findTokenByDegreeLeft(int degree) {
	for (std::list<Token>::iterator iter = _tokensLeft.begin(); iter != _tokensLeft.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return &*iter;
		}
	}
	return NULL;
}

Token	*Equation::findTokenByDegreeRight(int degree) {
	for (std::list<Token>::iterator iter = _tokensRight.begin(); iter != _tokensLeft.end(); iter++)
	{
		if (iter->getDegree() == degree) {
			return &*iter;
		}
	}
	return NULL;
}

// template <typename T>
void	Equation::add(coeffOpts coeff, int degree) {
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

void	Equation::sort() {
	_tokensLeft.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
	_tokensRight.sort([](const Token & t1, const Token & t2) {
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

void	Equation::simplify() {
	/* Takes all coefficients, turns them into rationals and finds gcd, 
	which we then divide the terms by
	==> make sure error margins don't fuck us up in this one */
	// Remove coefficient = 0 items

	/* find new highest degree */
	// std::list<Token>::iterator 	it = _tokens.begin();
	// Rational					result = doubleToRational(it->getCoeff());

	// ++it;
	// while (it != _tokens.end()) {
	// 	Rational	tmp = doubleToRational(it->getCoeff());
	// 	result = result.findGcd(tmp);
	// 	result.print();
	// 	++it;
	// }
	// setGcf(result);
	// for (std::list<Token>::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
	// 	auto coeffAsRational = Rational((*it).getCoeff());
	// 	auto newVal = coeffAsRational / result;
		
	// 	// Could this division lead to non-integer coefficients because of the division?
	// 	// There is a margin of error for conversion to rationals
	// 	// TODO: Nan / inf check?
	// 	if (newVal.getDenominator() != 0) {
	// 		(*it).setCoeff(std::round(newVal.getNumerator() / newVal.getDenominator()));
	// 	}
	// }
}
