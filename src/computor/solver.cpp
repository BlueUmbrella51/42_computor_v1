#include "headers/computor.h"

void		solve_equation(Equation &token_info) {
	if (token_info.getHighestDegree() <= 2) {
		token_info.simplify();
	}
	int		highest_degree = token_info.getHighestDegree();
	token_info.print();
	if (highest_degree == 0) {
		/* Only a constant is given, this is not an equation */
		throw std::invalid_argument("Invalid equation, only (non-zero) constant given.");
	}
	else if (highest_degree == 1) {
		/* Form: 2X = 4. 
		If ax = 0, X has to be 0. In all other cases, divide constant by 
		degree one coefficient and flip sign */
		if (token_info.findCoefficientOfDegree(0) == 0) {
			printf("Solution: X = 0.");
		}
		else if (token_info.findCoefficientOfDegree(1) == 0) {
			printf("No solutions can be found.");
		}
		else {
			/* Format a bit nicer, check if integer/double/Rational */
			printf("Solution: X = %lf", -(token_info.findCoefficientOfDegree(0) / token_info.findCoefficientOfDegree(1)));
		}
	}
	else if (highest_degree == 2) {
		
	}
}
