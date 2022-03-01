#include "headers/Equation.hpp"
#include <list>

Equation::Equation() : _side(Equation::operationSide::left) {
	_tokens = {};
	_highest_degree = -1;
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
	if (_highest_degree == -1) {
		findHighestDegree();
	}
	return _highest_degree;
}

// void	Equation::setHighestDegree(int n) {
// 	_highest_degree = n;
// }

Rational		&Equation::getGcf() {
	return (_gcf);
}

void			Equation::setGcf(Rational &x) {
	_gcf = x;
}

void	Equation::print() {
	printf("EQUATION\nhoghest degree: %d\n", _highest_degree);
	printf("GCF:\n");
	_gcf.print();
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
	Token *found = findTokenByDegree(degree);
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

void	Equation::findHighestDegree() {
	_highest_degree = 0;
	for (std::list<Token>::iterator iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		if (iter->getDegree() > _highest_degree) {
			_highest_degree = iter->getDegree();
		}
	}
}

void	Equation::simplify() {
	/* Takes all coefficients, turns them into rationals and finds gcd, 
	which we then divide the terms by
	==> make sure error margins don't fuck us up in this one */
	// Remove coefficient = 0 items
	for (std::list<Token>::iterator iter = _tokens.begin(); iter != _tokens.end();) {
		if (iter->getCoeff() == 0) {
			iter = _tokens.erase(iter);
		}
		else {
			++iter;
		}
	}
	/* find new highest degree */
	findHighestDegree();
	std::list<Token>::iterator 	it = _tokens.begin();
	Rational					result = doubleToRational(it->getCoeff());

	++it;
	while (it != _tokens.end()) {
		Rational	tmp = doubleToRational(it->getCoeff());
		result = result.findGcd(tmp);
		result.print();
		++it;
	}
	setGcf(result);
	for (std::list<Token>::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
		auto coeffAsRational = Rational((*it).getCoeff());
		auto newVal = coeffAsRational / result;
		
		// Could this division lead to non-integer coefficients because of the division?
		// There is a margin of error for conversion to rationals
		// TODO: Nan / inf check?
		if (newVal.getDenominator() != 0) {
			(*it).setCoeff(std::round(newVal.getNumerator() / newVal.getDenominator()));
		}
	}
}
