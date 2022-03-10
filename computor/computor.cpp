#include "computor.h"

int main(int argc, char *argv[]) {
	Rational r = doubleToRational(18719871987.386867198719871912312312, 0);
	r.print();
	printf("checks out %d\n", r.getNumerator() / r.getDenominator() == 4907302122261543/262144);
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
