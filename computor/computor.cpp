#include "computor.h"

int main(int argc, char *argv[]) {
	std::string help = "Usage: enter a polynomial of degree smaller than or equal to two.\nFactors can be: integers, \
decimals or fractions (form: 1/2 or 2(2/3)).\n\nExample: \"2X^2 - X = 2.25\"\n\nAccepts one indeterminate that must be called 'X'.\n";
	if (argc == 1) {
		std::cout << help;
		return (0);
	}
	else if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected exactly one.";
		return (1);
	}
	std::string input = argv[1];
	try {
		Equation eq = parse_equation(input);
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
