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
		// enum ConstantType {
		// 	constant, zero_degree
		// };
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
		// void					setConstType(ConstantType t);
		void					add(Token token);
		void					simplify();
		void					reduce();
		int						getHighestDegree() const;
		bool					hasZeroDegreeTokens() const;
		std::optional<Token>	findTokenOfDegree(std::list<Token> &tokens, int degree) const;
		Rational				findCoeffOfDegree(std::list<Token> &tokens, int degree) const;
		Equation::operationSide	getSide() const;
		void					setSide(Equation::operationSide s);
		void					factor(std::list<Token> &lst);
		Equation				&toNumerical();
		friend std::ostream		&operator<<(std::ostream &os, const Equation &eq);

	private:
		// ConstantType			_constType;
		std::list<Token>		_tokensLeft;
		std::list<Token>		_tokensRight;
		int						_highest_degree;
		Equation::operationSide	_side;
		void					findHighestDegreeLeft();
		void					moveTokensLeft();
		void					sortTokens(std::list<Token> &lst, int direction = 1);
		void					combineTokensByDegree(std::list<Token> &lst);
		void					removeZeroCoeff(std::list<Token> &lst);
};

Equation		doParseEquation(std::string &input);
Token			doParseToken(ParseToken &pt);

#endif
