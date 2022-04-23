#ifndef EQUATION_H
# define EQUATION_H
#include <list>
#include <stdio.h>
#include <iostream>
#include <optional>
#include <numeric>
#include "Token.h"
#include "Fraction.h"
#include "math_helpers.h"
#include "Rational.h"
#include "ParseToken.h"

class Equation {	
	public:
		enum operationSide {
			left,
			right
		};
		Equation();
		~Equation() = default;
		operator				std::string() const;
		Equation				&operator-=(const Token &t);
		Equation				&operator+=(const Token &t);
		Equation				&operator/=(const Token &t);
		template<typename T, 
			typename std::enable_if_t<std::is_integral<T>::value, bool> = true
		>
		Equation				&operator/=(T rhs) {
			for (auto it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
				(*it).setCoeff((*it).getCoeff() / rhs);
			}
			for (auto it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
				(*it).setCoeff((*it).getCoeff() / rhs);
			}
			return *this;
		}
		std::list<Token>		&getEquationLeft();
		std::list<Token>		&getEquationRight();
		void					add(Token token);
		void					simplify();
		int						getHighestDegree();
		std::optional<Token>	findTokenOfDegree(std::list<Token> &tokens, int degree);
		Rational				findCoeffOfDegree(std::list<Token> &tokens, int degree);
		Equation::operationSide	getSide();
		void					setSide(Equation::operationSide s);
		void					factor(std::list<Token> &lst);
		Equation				&toNumerical();

	private:
		std::list<Token>		_tokensLeft;
		std::list<Token>		_tokensRight;
		int						_highest_degree;
		Equation::operationSide	_side;
		void					findHighestDegreeLeft();
		void					moveTokensLeft();
		void					sortTokens(std::list<Token> &lst);
		void					combineTokensByDegree(std::list<Token> &lst);
		void					removeZeroCoeff(std::list<Token> &lst);

		friend std::ostream		&operator<<(std::ostream &os, const Equation &eq);
};
Token			parse_token(ParseToken &pt);
Equation		parse_equation(std::string &input);

#endif
