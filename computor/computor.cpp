#include "computor.h"

int main(int argc, char *argv[]) {
	std::string help = "Usage: enter a polynomial of degree smaller than or equal to two.\nFactors can be: integers, \
decimals or fractions (form: 1/2 or 2(2/3)).\n\nExample: \"2X^2 - X = 2.25\"\n\nAccepts one indeterminate that must be\
 called 'X'.\n\nOptions:\n-n		Numerical output only (default is scientific/precise notation.)\n";
	bool	numerical_mode = false;

	if (argc == 1) {
		std::cout << help;
		return (0);
	}
	else if (argc != 2 && argc != 3) {
		std::cerr << "Invalid number of arguments: expected exactly one and optionally -n.";
		return (1);
	}
	std::string input;
	if (argc == 3) {
		if ((std::string)argv[1] == "-n") { 
			input = argv[2];
			numerical_mode = true;
		}
		else if ((std::string)argv[2] == "-n") { 
			input = argv[1];
			numerical_mode = true;
		}
		else {
			std::cerr << "Invalid arguments: expected exactly one and optionally -n.";
			return (1);
		}
	}
	else {
		input = argv[1];
	}
	try {
		Equation eq = doParseEquation(input);
		if (numerical_mode) {
			eq.toNumerical();
		}
		std::cout << "Original equation:\n" << eq << "\n";
		eq.simplify();
		std::cout << "Reduced form:\n" << eq << "\n";
		std::cout << "Polynomial degree: " << eq.getHighestDegree() << "\n";
		Solution s = solve_equation(eq);
		std::cout << s << "\n";
		return (0);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	catch (std::overflow_error &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
