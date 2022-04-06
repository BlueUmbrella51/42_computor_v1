#include "computor.h"
#include "Radical.h"

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

// std::pair<Rational, Rational>	getRadical(Rational discriminant) {
// 	Rational whole;
// 	Rational radical;
// 	try {
// 		auto [w, r] = simplify_radical(abs(discriminant), 2);
// 		whole = Rational(w);
// 		radical = Rational(r);
// 	}
// 	catch (std::overflow_error &e) {
// 		discriminant.toFloating();
// 		auto [w, r] = simplify_radical(abs(discriminant), 2);
// 		whole = Rational(w);
// 		radical = Rational(r);
// 	}
// 	return std::make_pair(whole, radical);
// }

// void		solve_abc_formula(Rational &a, Rational &b, Rational &d) {
// 	try {
// 		auto [whole, radical] = simplify_radical(abs(d), 2);
// 		std::cout << "whole: " << whole << " Radical: " << radical << "\n";

// 	}
// 	catch (std::overflow_error &e) {
// 		d.toFloating();
// 		auto [whole, radical] = simplify_radical(abs(d), 2);
// 		std::cout << std::setprecision(150) << d;
// 		std::cout << "whole: " << whole << " Radical: " << radical << "\n";

// 	}
// 	auto divisor = 2 * a;
// 	Rational sol1;
// 	Rational sol2;

// 	// if (radical == 1 || radical == 0) {
// 	// 	// Radical irrelevant
// 	// 	sol1 = (-b + whole) / divisor;
// 	// 	sol2 = (-b - whole) / divisor;
// 	// 	std::cout << "X = " << sol1 << "\nX = " << sol2 << "\n"; 
// 	// }
// 	// // auto sol1 = (coeff_a - simplify_radical(discriminant)) / (2 * coeff_a);
// 	// // auto [whole, radical] = simplify_radical(125, 2);
// 	// auto n = -b / divisor;
// 	// auto m = whole / divisor;
// 	// std::cout << "Discriminant is strictly positive, the two solutions are:\n";
// 	// std::cout << "X = " << n;
// 	// if (m != 0) 
// 	// 	std::cout  << " + " << m << "sqrt(" << radical << ")\n";
// 	// std::cout << "X = " << n << " - " << m << "sqrt(" << radical << ")\n"; 
// }

void		solve_second_degree(Equation &eq) {
	auto a_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 2));
	auto b_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 1));
	auto c_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 0));

	Rational a = a_token ? a_token.value().getCoeff(): 0;
	Rational b = b_token ? b_token.value().getCoeff(): 0;
	Rational c = c_token ? c_token.value().getCoeff(): 0;

	// TODO: try?
	auto discriminant = (b * b) - (4 * a * c);

	Radical r = Radical(discriminant, 2);
	std::cout << r;
	// auto [whole, radical] = getRadical(discriminant);
	// if (a.isFloating() || b.isFloating() || radical.isFloating()) {
	// 	a.toFloating();
	// 	b.toFloating();
	// 	discriminant.toFloating();
	// }
	// std::cout << "A: " << a << "\nB: " << b << "\nC: " << c << "\n";
	// std::cout << "Discriminant: " << discriminant << "\n";
	// std::cout << "Whole: " << whole << "\nRadical: " << radical << "\n";
	// if (discriminant == 0) {
	// 	// Just one solution: -b / 2a
	// }
	// else if (radical == 0 || radical == 1 || discriminant.isFloating()) {
	// 	// TODO radical can't be 0?
	// 	// Radical is irrelevant in this case
	// 	if (discriminant.isFloating()) {
	// 		auto d = std::sqrt(radical.getFloat());
	// 		auto sol1 = (-b + d) / (2 * a);
	// 		auto sol2 = (-b - d) / (2 * a);
	// 		std::cout << -b << " +/- " << d << "/" << 2 * a << "\n";
	// 		if (discriminant < 0)
	// 			std::cout << "Solutions:\nX = " << sol1 << "i\nX = " << sol2 << "i\n";
	// 		else 
	// 			std::cout << "Solutions:\nX = " << sol1 << "\nX = " << sol2 << "\n";
	// 	}
	// 	else {
	// 		// Ignore radical for now

	// 	}
	// }
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
