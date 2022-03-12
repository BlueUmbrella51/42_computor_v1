#include "computor.h"


void		solve_first_degree(Equation &token_info) {
	/* Form: 2X = 4. 
	If ax = 0, X has to be 0. In all other cases, divide constant by 
	degree one coefficient and flip sign */
	token_info = token_info;
	// if (token_info.findTokenByDegreeLeft(0) == 0) {
	// 	printf("Solution: X = 0.");
	// }
	// else if (token_info.findTokenByDegreeLeft(1) == 0) {
	// 	printf("No solutions can be found.");
	// }
	// else {
	// 	/* Format a bit nicer, check if integer/double/Rational */
	// 	printf("Solution: X = %lf", -((token_info.findTokenByDegreeLeft(0)) / (token_info.findTokenByDegreeLeft(1))));
	// }
}

// void		solve_second_degree(Equation &token_info) {
// 	double a = token_info.findCoefficientOfDegree(2);
// 	double b = token_info.findCoefficientOfDegree(1);
// 	double c = token_info.findCoefficientOfDegree(0);

// 	printf("A %lf B %lf C %lf\n", a, b, c);
// 	if (a == 0) {
// 		throw std::invalid_argument("Coefficient of the second degree term cannot be zero.");
// 	}
// 	double	discriminant = std::pow(b, 2.0) - (4 * a * c);
// 	printf("Discriminant: %lf\n", discriminant);

// 	/*
// 	A positive discriminant indicates that the quadratic has two distinct real number solutions.
// 	A discriminant of zero indicates that the quadratic has a repeated real number solution.
// 	A negative discriminant indicates that neither of the solutions are real numbers.

// 	Square root of negative number n is sqrt(n) * sqrt(-1), sqrt(-1) = i (solve complex solutions)

// 	formula to solve: (-b +/- sqrt(discriminant)) / 2a
// 	*/
// 	if (discriminant > 0) {
// 		//TODO: simplify radical!
// 		/* TODO: factor to solve? */
// 		printf("Discriminant is greater than zero, equation has two real roots.\n");
// 		double solution_one = (-b + std::sqrt(discriminant))/ (2 * a); // (-b + discriminant)/2a
// 		double solution_two = (-b - std::sqrt(discriminant))/ (2 * a); // (-b + discriminant)/2a
// 		printf("The solutions are: x = %lf and x = %lf.\n", solution_one, solution_two);
// 	}
// 	else if (discriminant == 0) {
// 		printf("Discriminant is zero, equation has one real root.\n");
// 		double solution = (-b + std::sqrt(discriminant))/ (2 * a);
// 		printf("The solution is: x = %lf.\n", solution);
// 	}
// 	else {
// 		printf("Discriminant is smaller than zero, equation has two complex roots.\n");
// 		// -b +/- sqrt(-discriminant) * i (== sqrt(-1))
// 		double real_sol1 = -b / (2 * a);
// 		double imag_part = std::sqrt(-discriminant) / (2 * a);

// 		// printing should be handled by class
// 		printf("The solutions are: x = %lf + %lfi and x = %lf - %lfi.\n", 
// 		real_sol1, imag_part, real_sol1, imag_part);
// 	}
// }

void		solve_equation(Equation &token_info) {
	// int		highest_degree = token_info.getHighestDegree();

	// if (highest_degree == 0) {
	// 	/* Only a constant is given, this is not an equation */
	// 	throw std::invalid_argument("Invalid equation, only (non-zero) constant given.");
	// }
	// else if (highest_degree == 1) {
	// 	solve_first_degree(token_info);
	// }
	// else if (highest_degree == 2) {
	// 	solve_second_degree(token_info);
	// }
	// else {
	// 	throw std::invalid_argument("Degree is greater than two, cannot solve.");
	// }
}
