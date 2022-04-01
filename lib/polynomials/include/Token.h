#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Rational.h"
#include "Real.h"
#include "math_helpers.h"
#include <variant>

class Token
{
	public:
		Token(Real coeff, long degree = 0);
		~Token() = default;
		// Token		&operator-=(const Token &t);
		// Token		&operator+=(const Token &t);
		// Token		&operator/=(const Token &t);
		// Token		&operator*=(const Token &t);
		operator	std::string() const;
		long		getDegree() const;
		Real		getCoeff() const;
		void		setCoeff(Real coeff);

	private:
		Real		_coeff;
		long		_degree;
	
	friend std::ostream	&operator<<(std::ostream &os, const Token &r);
	friend bool			operator==(const Token &lhs, const Token &rhs);
};

#endif
