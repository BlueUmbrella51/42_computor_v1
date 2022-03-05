

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
		std::list<Token>	&getTokens();
		Rational	&getGcf();
		void		setGcf(Rational &x);
		void		print();
		void		add(double coeff, int degree);
		void		sort();
		void		simplify();
		int			getHighestDegree();
		// void		setHighestDegree(int n);
		void		findHighestDegree();
		double		findCoefficientOfDegree(int degree);
		Equation::operationSide	getSide();
		void		setSide(Equation::operationSide s);

	private:
		std::list<Token>		_tokens;
		int						_highest_degree;
		Equation::operationSide	_side;
		Rational				_gcf;
		Token					*findTokenByDegree(int degree);
};

#endif
