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
// class Parser {
// 	private:
// 		typedef int (*boolFunctionType)(int);
// 		int		 isplusormin(int c) {
// 			return (c == '+' || c == '-');
// 		};
// 		int		ismatch(int c) {
// 			if (_var == '0') {
// 				setVar(c);
// 				return (true);
// 			}
// 			if (_var == c) {
// 				return true;
// 			}
// 			return false;
// 		}
// 		enum operationSide {
// 			left,
// 			right
// 		};
// 		enum	expectedType {
// 			digit,
// 			sign,
// 			var
// 		};
// 		std::map<expectedType, boolFunctionType>	expectedChecker = {
// 			{ sign, isplusormin },
// 			{ digit, isdigit },
// 			{ var, ismatch }
// 		};
// 		operationSide			_side;
// 		char					_var;
// 		bool				 	(*isExpected)(char);

// 	public:
// 		Parser();
// 		~Parser();
// 		void	setVar(char c);
// 		char	getVar();
// 		bool	varIsSet();
// };

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
		// void	combine();
};

#endif
