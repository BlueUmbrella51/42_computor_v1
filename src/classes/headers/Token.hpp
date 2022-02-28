#ifndef TOKEN_HPP
# define TOKEN_HPP
#include <stdio.h>
#include <iostream>
#include "Rational.hpp"
#include "../../math/headers/math_helpers.hpp"

class Token
{
	private:
		double		_coeff;
		int			_degree;

	public:
		Token(double coeff, int degree);
		~Token();
		void		print();
		int			getDegree() const;
		double		getCoeff()	const;
		void		setCoeff(double n);
		bool   		operator==(const Token &x);
		// Rational	coeffToRational();
};

#endif
