#include "computor.h"
#include "Root.h"

int main(int argc, char *argv[]) {
	// TODO help text
	Root r = Root(125.12);
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (1);
	}
	std::string input = argv[1];
	try {
		Equation eq = parse_equation(input);
		std::cout << "Original equation:\n" << eq << "\n";
		eq.simplify();
		std::cout << "Simplified representation of equation:\n" << eq << "\n";
		std::cout << "Highest degree: " << eq.getHighestDegree() << "\n";
		solve_equation(eq);
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
