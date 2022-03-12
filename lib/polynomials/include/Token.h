#ifndef TOKEN_H
# define TOKEN_H
#include <stdio.h>
#include <iostream>
#include "Rational.h"
#include "math_helpers.h"
#include <variant>

class Token
{
	public:
		typedef 	std::variant<long double, long long, Rational> coeffOpts; 
		// template <typename T>
		Token(coeffOpts coeff, int degree = 0);
		// Token();
		~Token();
		void		print()	const;
		int			getDegree() const;
		coeffOpts	getCoeff()	const;
		void		setCoeff(Token::coeffOpts coeff);
		bool   		operator==(const Token &x);
		// Rational	coeffToRational();
	private:
		coeffOpts	_coeff;
		long int	_degree;
};

Token				operator*(const Token &t, long long n);
Token				operator+(const Token &lhs, Token &rhs);
Token::coeffOpts	getGcd(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs);
Token::coeffOpts		operator/(const Token::coeffOpts &lhs, const Token::coeffOpts &rhs);
#endif
