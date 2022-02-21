#ifndef TOKEN_HPP
# define TOKEN_HPP
# include "../headers/computor.h"
# include <optional> 
# include <list>
# include <map>

enum operationSide {
	left,
	right
};

class Token
{
	private:
		// char	_sign;
		double	_coeff;
		int		_degree;
		// std::optional<Variable> _var;

	public:
		Token(float coeff, int degree);
		~Token();
		void	print();
		int		getDegree() const;
		double	getCoeff()	const;
		void	setCoeff(double c);
};

class Tokens {
	private:
		std::optional<char>	_variable;
		std::list<Token>	_tokens;
		int					_highest_degree;
		Token				*has_degree(int degree);
	
	public:
		Tokens();
		~Tokens();
		std::list<Token>	getTokens();
		void	setVar(char var);
		std::optional<char>	getVar();
		void	print();
		void	add(double coeff, int degree);
		void	sort();
		int		getHighestDegree();
		void	setHighestDegree(int n);
		// void	combine();
};

#endif
