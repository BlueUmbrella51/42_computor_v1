#include "headers/computor.h"

double		get_coefficient(std::string &str, size_t *i, Equation::operationSide side) {
	bool	dotFound = false;
	double 	coeff = atof(&(str[*i]));

	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
    if (coeff == 0 && str[*i] != '0') {
		coeff = 1;
	}
	if (coeff == 0 && str[*i] != '0') {
		coeff = 1;
	}
	while (*i < str.length() && 
	(isdigit(str[*i]) || (str[*i] == '.' && dotFound == false))) {
		if (str[*i] == '.') {
			dotFound = true;
		}
		(*i)++;
	}
	// Not safe yet
	return side == Equation::operationSide::right ? -coeff : coeff;
}

/* Make sure if strlen check is neccessary */
int		get_degree(std::string &str, size_t *i) {
	int degree = 0;
	if (str[*i] != '*') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (str[*i] != 'X') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (str[*i] != '^') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (!isdigit(str[*i]) && !(str[*i] == '+')) {
		throw std::invalid_argument("Syntax error");
	}
	degree = atoi(&(str[*i]));
	if (str[*i] == '+') {
		(*i)++;
	}
	while (*i < str.length() && isdigit(str[*i])) {
		(*i)++;
	}
	return (degree);
}

/* Assumes format of a * x ^ p where a is a number, x a character in the al*/
void	parse_token(Equation *token_info, std::string &str, size_t *i) {
	try {
		double	coeff = get_coefficient(str, i, token_info->getSide());
		int		degree = get_degree(str, i);
		token_info->add(coeff, degree);
	}
	catch (std::invalid_argument& e) {
		throw (e);
	}
}

Equation	parse_equation(std::string &equation) {
	// Equation::operationSide side = Equation::operationSide::left;
	Equation token_info = Equation();
	equation.erase(std::remove_if(equation.begin(), equation.end(), ::isspace),
	equation.end());
	size_t i = 0;
	while (i < equation.length())
	{
		try {
			if (equation[i] == '=') {
				if (token_info.getTokens().empty()) {
					throw std::invalid_argument("Starting with equals sign is illegal.");
				}
				if (token_info.getSide() != Equation::operationSide::left) {
					throw std::invalid_argument("Only one equals sign allowed per equation.");
				}
				i++;
				token_info.setSide(Equation::operationSide::right);
			}
			parse_token(&token_info, equation, &i);
		}
		catch (std::invalid_argument &e) {
			throw;
		}
	}
	if (token_info.getSide() == Equation::operationSide::left) {
		throw std::invalid_argument("No equals sign found, not a valid equation.");
	}
	token_info.sort();
	return token_info;
}