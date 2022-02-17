#include "../headers/computor.h"
#include "../headers/token.hpp"

/* Handle atof error? 
WE NEED TO KNOW SIDE OF EQUATION!!
*/
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
	printf("SIDE %u\n", side);
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
	// int number = atoi(equation.c_str());
	token_info->getVar();
	try {
		double	coeff = get_coefficient(str, i, side);
		printf("After get coeff %s\n", &str[*i]);
		std::cout << "Coeff: " << coeff << std::endl;
		int		degree = get_degree(str, i);
		printf("After get degree %s\n", &str[*i]);
		std::cout << "Degree: " << degree << std::endl;
		std::cout << "Rest: " << &str[*i] << std::endl;
				token_info->add(coeff, degree);
	}
	catch (std::invalid_argument& e) {
		throw (e);
	}
	// char	*s = *equation;
	// std::cout <<  ? 'X' : '0' << std::endl;
	/* 
	1. Skip one or zero of [ + , - ]
	2. Skip any number of digits, including zero. If zero digits, coeff is 1
	else, atoi	--> previous steps give coefficient
	3. Skip one '*' (optional)
	4. Parse one upper- or lowercase variable (optional, but mandatory if there
	was no digit, has to be alpabetic)
	5. Is next (non-whitespace) character '^'?
		yes: skip it
			is next digits?
				yes: parse all digits after it (minimum of one)
				no: error
		no: 
		Is next digit(s)?
			yes: parse digits as degree, then skip
		skip until next non-whitespace. Has to be '-' or '+'
	*/
	// *equation = &((*equation)[3]);
}

Tokens	parse_tokens(std::string &equation) {
	/* */
	// Parser parser = Parser();
	operationSide side = left;
	Tokens token_info = Tokens();
	equation.erase(std::remove_if(equation.begin(), equation.end(), ::isspace),
	equation.end());
	// std::string::iterator iter = equation.begin();
	std::cout << equation << std::endl;
	size_t i = 0;
	while (i < equation.length())
	{
		try {
			printf("character %c\n", equation[i]);
			if (equation[i] == '=') {
				printf("EQUALS FOUND\n\n");
				if (token_info.getTokens().empty()) {
					throw std::invalid_argument("Starting with equals sign is illegal.");
				}
				if (side != left) {
					throw std::invalid_argument("Only one equals sign allowed per equation.");
				}
				printf("CHANGE SIDES\n\n");
				i++;
				side = right;
			}
			parse_token(&token_info, equation, &i, side);
			// printf("%s\n", equation);
		}
		catch (std::invalid_argument &e) {
			throw;
		}
		// exit(1);
	}
	token_info.sort();
	token_info.print();
	return token_info;
	// exit (0);
	// throw std::invalid_argument("Unexpected token in input.");
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (-1);
	}
	// Token a = Token(-1, 0);
	// Token b = Token(13, 8);
	// Token c = Token(2, 4);
	// // a.print();
	// // b.print();
	// // c.print();
	// Tokens expression = Tokens('x');
	// expression.add(a);
	// expression.add(b);
	// expression.add(c);
	// // expression.print();
	// expression.sort();
	// expression.print();
	// std::cout << std::endl;
	// expression.combine();
	// expression.print();
	// std::cout << argv[1];
	// std::cout << argc;
	Tokens token_info = Tokens();
	std::string equation = argv[1];
	try {
		Tokens token_info = parse_tokens(equation);
	}
	catch (std::invalid_argument& e) {
		std::cerr << "ERROR" << e.what() << std::endl;
		return (1);
	}
}
