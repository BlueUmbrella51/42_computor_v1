#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Rational.h"
#include "math_helpers.h"

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
