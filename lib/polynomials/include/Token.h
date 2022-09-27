#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Fraction.h"
#include "Rational.h"
#include "math_helpers.h"
#include <variant>

class Token
{
	public:
		Token(Rational coeff, long degree, bool isConst = false);
		~Token() = default;
		operator	std::string() const;
		long		getDegree() const;
		Rational	getCoeff() const;
		bool		isConstant() const;
		void		setCoeff(Rational coeff);

	private:
		Rational	_coeff;
		long		_degree;
		bool		_isConst;
	
	friend std::ostream	&operator<<(std::ostream &os, const Token &r);
	friend bool			operator==(const Token &lhs, const Token &rhs);
};

#endif
