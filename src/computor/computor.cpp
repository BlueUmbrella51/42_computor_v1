#include "headers/computor.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments: expected one.";
		return (1);
	}
	std::string equation = argv[1];
	// Rational n = doubleToRational(1303478);
	// n.print();
	// exit(0);
	try {
		Equation token_info = parse_equation(equation);
		solve_equation(token_info);
		// if (token_info.getHighestDegree() == 0) {
		// 	// We just have a constant, which is the answer, or rather, there is no solution?;
		// 	printf("The solution is: %lf.\n", token_info.findCoefficientOfDegree(0));
		// }
		// else if (token_info.getHighestDegree() == 1) {
		// 	// Just divide constant by 1st degree coeff
		// 	token_info.simplify();
		// 	printf("After simplify:\n");
		// 	token_info.print();
		// 	double zeroCoeff = token_info.findCoefficientOfDegree(0);
		// 	zeroCoeff = -zeroCoeff;
		// 	double oneCoeff = token_info.findCoefficientOfDegree(1);
		// 	printf("zero coeff: %lf\none coeff %lf\n", zeroCoeff, oneCoeff);
		// 	if (oneCoeff == 0) {
		// 		printf("No solutions could be found.");
		// 		return (1);
		// 	}
		// 	// zeroCoeff /= token_info.findCoefficientOfDegree(1);
		// 	printf("The solution is: %lf.\n", zeroCoeff/oneCoeff);
		// }
		// else if (token_info.getHighestDegree() == 2) {
		// 	// complete the square/abc formula
		// 	token_info.simplify();
		// }
		// else {
		// 	throw std::invalid_argument("Degree is larger than 2.");
		// }
		// token_info.print();
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
