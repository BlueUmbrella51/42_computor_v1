#ifndef TOKEN_HPP
# define TOKEN_HPP
# include "../headers/computor.h"
# include <optional> 
# include <list>

class Token
{
	private:
		// char	_sign;
		float	_coeff;
		int		_degree;
		// std::optional<Variable> _var;

	public:
		Token(float coeff, int degree);
		~Token();
		void	print();
		int		getDegree() const;
		float	getCoeff()	const;
};

class Tokens {
	private:
		char				_variable;
		std::list<Token>	_tokens;
	
	public:
		Tokens(char var);
		~Tokens();
		void	setVar(char var);
		void	print();
		void	add(Token);
		void	sort();
		void	combine();
};

#endif
