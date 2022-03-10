#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Rational.h"
#include "math_helpers.h"
#include <variant>

using coeffOpts = std::variant<long double, long long, Rational>;

class Token
{
	private:
		coeffOpts	_coeff;
		int			_degree;

	public:
		// template <typename T>
		Token(coeffOpts coeff, int degree);
		Token();
		~Token();
		void		print();
		int			getDegree() const;
		double		getCoeff()	const;
		// void		setCoeff(double n);
		bool   		operator==(const Token &x);
		// Rational	coeffToRational();
};

#endif
