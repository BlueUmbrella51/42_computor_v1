#include "headers/computor.h"

double		get_coefficient(std::string &str, size_t *i, Tokens::operationSide side) {
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
	return side == Tokens::operationSide::right ? -coeff : coeff;
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
void	parse_token(Tokens *token_info, std::string &str, size_t *i) {
	try {
		double	coeff = get_coefficient(str, i, token_info->getSide());
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
			parse_token(&token_info, equation, &i);
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
// 	printf("GCD of (0, 0) %ld\nGCD of (21, 4) %ld\nGCD of (2, 2) %ld\n\
// GCD of (9, 36) %ld\n", gcd(0,0), gcd(21, 4), gcd(2,2), gcd(9, 36));
	Rational n = Rational(-1, -2);
	n.print();
	try {
		double n = (double)-4/8;
		Rational v = doubleToRational(n);
		printf("\n\nRATIONAL FROM DOUBLE:\n");
		v.print();
	}
	catch (std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}
	// n.print();
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
