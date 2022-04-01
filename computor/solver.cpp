#include "computor.h"

void		solve_first_degree(Equation &eq) {
	/* Form: 2X = 4. 
	If ax = 0, X has to be 0. In all other cases, subtract or add 
	coefficient of degree 0 from both sides, then divide both sides
	by coefficient of degree 1. */
	auto t = eq.findTokenOfDegree(eq.getEquationLeft(), 0);
	auto t1 = eq.findTokenOfDegree(eq.getEquationLeft(), 1);

	if (!t) {
		// Token found
		std::cout << "Solution: X = 0.\n";
	}
	else {
		/* If ax + b, solution is: -b / a */
		Token zeroDegr = t.value();
		Token firstDegr = t1.value();
		if (zeroDegr.getCoeff() > 0) {
			eq -= zeroDegr;
		}
		else {
			eq += zeroDegr;
		}
		// Divide both sides of equation by coefficient of degree 1
		eq /= firstDegr;
		auto sol = eq.findTokenOfDegree(eq.getEquationRight(), 0);
		std::cout << "Solution: X = " << sol.value()  << ".\n";
	}
}

void		solve_second_degree(Equation &eq) {
	/* Factor ax^2 + bx + c = 0 into :
	(x + d)(x + e) where:
	a == 1
	d + e == b
	d * e == c
	*/
	Equation bck = eq;

	try {
		eq.factor(eq.getEquationLeft());
	}
	catch (std::overflow_error &e) {
		std::cout << e.what();
		eq = bck;
	}
	std::cout << "After factor left: " << eq << "\n";
	auto a = (eq.findTokenOfDegree(eq.getEquationLeft(), 2));
	auto b = (eq.findTokenOfDegree(eq.getEquationLeft(), 1));
	auto c = (eq.findTokenOfDegree(eq.getEquationLeft(), 0));

	Real coeff_a = a ? a.value().getCoeff(): 0;
	Real coeff_b = b ? b.value().getCoeff(): 0;
	Real coeff_c = c ? c.value().getCoeff(): 0;
	std::cout << "A: " << coeff_a << "\nB: " << coeff_b << "\nC: " << coeff_c << "\n";
	// if (multiplicationExceedsLimits(coeff_b, coeff_b) || 
	// multiplicationExceedsLimits(coeff_a, coeff_c) ||
	// multiplicationExceedsLimits(coeff_a * coeff_c, 4) ||
	// subtractionExceedsLimits(coeff_b * coeff_b, 4 * coeff_a * coeff_c)) {
	// 	std::cout << "Cannot find discriminant without causing overflow.\n";
	// 	throw std::overflow_error("Cannot find discriminant without causing overflow.\n");
	// }
	auto	discriminant = (coeff_b * coeff_b) - (4 * coeff_a * coeff_c);
	if (discriminant > 0) {
		/* Two real roots: -b + sqrt(d) and -b - sqrt(d) */
		auto [whole, radical] = simplify_radical(100, 2);
		std::cout << "Whole: " << whole << " Radical: " << radical << "\n";

		std::cout << "Discriminant is strictly positive, the two solutions are:\n";
	}
	else if (discriminant < 0) {
		/* Two complex roots: -b + sqrt(d) and -b - sqrt(d) 
		sqrt(n) where n < 0 == i*sqrt(abs(n))
		*/
		std::cout << "Discriminant is strictly negative, the two solutions are:\n";
	}
	else {
		// simplify_sqrt(std::get<int>(discriminant.getVal()));
		std::cout << "Discriminant is zero, the solution is:\n";
		/* In this case, solution is -b / 2a  */
		auto solution = -coeff_b / (2 * coeff_a);
		std::cout << solution << "\n";
	}
	/* So now we have to calculate: (-b +- sqrt(discriminant).)/2a */
// 	if (a == 0) {
}
// void		solve_second_degree(Equation &token_info) {
	
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

void		solve_equation(Equation &eq) {
	int		highest_degree = eq.getHighestDegree();

	std::cout << "Polynomial degree: " << highest_degree << "\n";
	if (highest_degree == 0) {
		/* Only a constant is given, this is not an equation */
		throw std::invalid_argument("Invalid equation, no variable to solve for.");
	}
	else if (highest_degree == 1) {
		solve_first_degree(eq);
	}
	else if (highest_degree == 2) {
		solve_second_degree(eq);
	}
	else {
		throw std::invalid_argument("Degree " + std::to_string(eq.getHighestDegree()) + " is strictly greater than two, cannot solve.");
	}
}
