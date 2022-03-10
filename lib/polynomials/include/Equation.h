

#ifndef EQUATION_H
# define EQUATION_H
#include <list>
#include <stdio.h>
#include <iostream>
#include <optional>
#include <numeric>
#include "Token.h"
#include "Rational.h"
#include "math_helpers.h"

class Equation {	
	public:
		enum operationSide {
			left,
			right
		};
		Equation();
		~Equation();
		std::list<Token>	&getEquationLeft();
		std::list<Token>	&getEquationRight();
		// Rational	&getGcf();
		// void		setGcf(Rational &x);
		void		print();
		// template <typename T>
		void		add(coeffOpts coeff, int degree);
		// void		add(Rational coeff, int degree);
		// void		add(long long int coeff, int degree);
		void		sort();
		void		simplify();
		int			getHighestDegree();
		// void		setHighestDegree(int n);
		int			findHighestDegree();
		double		findCoefficientOfDegree(int degree);
		Equation::operationSide	getSide();
		void		setSide(Equation::operationSide s);

	private:
		std::list<Token>		_tokensLeft;
		std::list<Token>		_tokensRight;
		int						_highest_degree;
		Equation::operationSide	_side;
		// Rational				_gcf;
		Token					*findTokenByDegreeRight(int degree);
		Token					*findTokenByDegreeLeft(int degree);
};

#endif
