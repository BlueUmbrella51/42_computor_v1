#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Rational.h"
#include "Number.h"
#include "math_helpers.h"
#include <variant>

class Token
{
	public:
		// typedef 	std::variant<long double, long long, Rational> coeffOpts; 
		// template <typename T>
		Token(Number coeff, long degree = 0);
		// Token();
		~Token();
		// void		print()	const;
		long		getDegree() const;
		Number		getCoeff() const;
		void		setCoeff(Number coeff);
		// bool   		operator==(const Token &x);
		// Rational	coeffToRational();
	private:
		Number		_coeff;
		long		_degree;
	
	friend std::ostream	&operator<<(std::ostream &os, const Token &r);
};

// Token				operator*(const Token &t, long long n);
// Token				operator+(const Token &lhs, Token &rhs);
// Token::coeffOpts	getGcd(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs);
// Token::coeffOpts		operator/(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs);
#endif
