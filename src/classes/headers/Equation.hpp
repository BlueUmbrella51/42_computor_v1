

#ifndef EQUATION_HPP
# define EQUATION_HPP
#include <list>
#include <stdio.h>
#include <iostream>
#include <optional>
#include <numeric>
#include "Token.hpp"
#include "Rational.hpp"
#include "../../math/headers/math_helpers.hpp"

class Equation {	
	public:
		enum operationSide {
			left,
			right
		};
		Equation();
		~Equation();
		std::list<Token>	&getTokens();
		std::optional<char>	getVar();
		Rational	&getGcf();
		void		setGcf(Rational &x);
		void		print();
		void		add(double coeff, int degree);
		void		sort();
		void		simplify();
		int			getHighestDegree();
		void		setHighestDegree(int n);
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