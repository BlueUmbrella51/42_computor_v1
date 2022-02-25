

#ifndef TOKENS_HPP
# define TOKENS_HPP
#include <list>
#include <stdio.h>
#include <iostream>
#include <optional>
#include "Token.hpp"

enum operationSide {
	left,
	right
};

class Tokens {	
	public:
		enum operationSide {
			left,
			right
		};
		Tokens();
		~Tokens();
		std::list<Token>	getTokens();
		std::optional<char>	getVar();
		void	print();
		void	add(double coeff, int degree);
		void	sort();
		int		getHighestDegree();
		void	setHighestDegree(int n);
		Tokens::operationSide	getSide();

	private:
		std::list<Token>		_tokens;
		int						_highest_degree;
		Tokens::operationSide	_side;
		Token					*has_degree(int degree);
};

#endif