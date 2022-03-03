#include "computor.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (1);
	}
	std::string equation = argv[1];
	try {
		Equation token_info = parse_equation(equation);
		printf("After parsing\n");
		token_info.print();
		solve_equation(token_info);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
