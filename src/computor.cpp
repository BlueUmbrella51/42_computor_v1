#include "../headers/computor.h"
#include "../headers/token.hpp"

/* Handle atof error? 
WE NEED TO KNOW SIDE OF EQUATION!!
*/

// int		findGCD(std::vector<int> numbers) {
// 	int result = numbers[0];
// 	for (int i = 1; i < numbers.length; i++) {
// 		result = gcd(result, numbers[i]);
// 	}
// 	return result;
// }

double		get_coefficient(std::string &str, size_t *i, operationSide side) {
	bool	dotFound = false;
	double 	coeff = atof(&(str[*i]));

	if (coeff == 0 && str[*i] != '0') {
		coeff = 1;
	}
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
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
	return side == right ? -coeff : coeff;
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
	if (!isdigit(str[*i]) && !(str[*i] == '-' || str[*i] == '+')) {
		throw std::invalid_argument("Syntax error");
	}
	degree = atoi(&(str[*i]));
	if (str[*i] == '+' || str[*i] == '-') {
		(*i)++;
	}
	while (*i < str.length() && isdigit(str[*i])) {
		(*i)++;
	}
	return (degree);
}

/* Assumes format of a * x ^ p where a is a number, x a character in the al*/
void	parse_token(Tokens *token_info, std::string &str, size_t *i,
operationSide side) {
	token_info->getVar();
	try {
		double	coeff = get_coefficient(str, i, side);
		int		degree = get_degree(str, i);
		token_info->add(coeff, degree);
	}
	catch (std::invalid_argument& e) {
		throw (e);
	}
}

Tokens	parse_tokens(std::string &equation) {
	operationSide side = left;
	Tokens token_info = Tokens();
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
				if (side != left) {
					throw std::invalid_argument("Only one equals sign allowed per equation.");
				}
				i++;
				side = right;
			}
			parse_token(&token_info, equation, &i, side);
		}
		catch (std::invalid_argument &e) {
			throw;
		}
	}
	if (side == left) {
		throw std::invalid_argument("No equals sign found, not a valid equation.");
	}
	token_info.sort();
	token_info.print();
	return token_info;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (-1);
	}
	std::string equation = argv[1];
	try {
		Tokens token_info = parse_tokens(equation);
		if (token_info.getHighestDegree() > 2) {
			throw std::invalid_argument("Degree is larger than 2.");
		}
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
