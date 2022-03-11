#include "computor.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (1);
	}
	std::string input = argv[1];
	try {
		Equation token_info = parse_equation(input);
		token_info.simplify();
		solve_equation(token_info);
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
