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
		/* Check if coefficient of degree two is one, if so, find number where 
		x1 * x2 = c and x1 + x2 =  b,
		else magic x */
		double a = token_info.findCoefficientOfDegree(2);
		double b = token_info.findCoefficientOfDegree(1);
		double c = token_info.findCoefficientOfDegree(0);

		printf("A %lf B %lf C %lf\n", a, b, c);
		// double top_x = a * c;
		// double bot_x = b;
		// find x1 and x2 where x1 * x2 = top_x and x1 + x2 = bot_x
		// printf("Top x %lf, bot x %lf\n", top_x, bot_x);
		// b^2 - 4ac
		double	discriminant = std::pow(b, 2.0) - (4 * a * c);
		printf("Discriminant: %lf\n", discriminant);
		/*
		A positive discriminant indicates that the quadratic has two distinct real number solutions.
		A discriminant of zero indicates that the quadratic has a repeated real number solution.
		A negative discriminant indicates that neither of the solutions are real numbers.

		Square root of negative number n is sqrt(n) * sqrt(-1), sqrt(-1) = i (solve complex solutions)

		formula to solve: (-b +/- sqrt(discriminant)) / 2a
		*/
		if (discriminant > 0) {
			//TODO: simplify radical!
			/* TODO: factor to solve? */
			printf("Discriminant is greater than zero, equation has two real roots.\n");
			double solution_one = (-b + std::sqrt(discriminant))/ (2 * a); // (-b + discriminant)/2a
			double solution_two = (-b - std::sqrt(discriminant))/ (2 * a); // (-b + discriminant)/2a
			printf("The solutions are: x = %lf and x = %lf.\n", solution_one, solution_two);
		}
		else if (discriminant == 0) {
			printf("Discriminant is zero, equation has one real root.\n");
			double solution = (-b + std::sqrt(discriminant))/ (2 * a);
			printf("The solution is: x = %lf.\n", solution);
		}
		else {
			printf("Discriminant is smaller than zero, equation has two complex roots.\n");
			// -b +/- sqrt(-discriminant) * i (== sqrt(-1))
			double real_sol1 = -b / (2 * a);
			double imag_part = std::sqrt(-discriminant) / (2 * a);

			// printing should be handled by class
			printf("The solutions are: x = %1$lf + %2$lfi and x = %1$lf - %2$lfi.\n", 
			real_sol1, imag_part);
		}
	}
}
