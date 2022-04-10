#include "computor.h"
#include "Root.h"
#include "Solution.h"

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
	std::cout << "Solve second degree\n";
	auto a_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 2));
	auto b_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 1));
	auto c_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 0));

	Rational a = a_token ? a_token.value().getCoeff(): Rational(0);
	Rational b = b_token ? b_token.value().getCoeff(): Rational(0);
	Rational c = c_token ? c_token.value().getCoeff(): Rational(0);

	// TODO: try?
	std::cout << "A: " << a << " B: " << b << " C: " << c << "\n";
	std::cout << "B^2: " << (b * b) << "- 4AC: " << (4 * a*c) << "\n";
	Rational discriminant = (b * b) - (4 * a * c);
	
	std::cout << "Discriminant: " << discriminant << "\n";
	
	if (discriminant != 0) {
		Rational divisor = (2 * a);
		Rational left = -b / divisor;
		Root right = Root(discriminant) / divisor;

		std::cout << "Left: " << left << "\nRight: " << right << "\n";
		// TODO: can it be numerically solved? (Anything is a float or root doesn't matter)
		Solution plus = Solution(Solution::Sign::plus, left, right);
		Solution minus = Solution(Solution::Sign::minus, left, right);

		std::cout << "Solutions:\nX = " << plus << "\nX = " << minus << "\n";
	}
	else {
		auto solution = -b / (2 * a);
		std::cout << "Solution:\n" << solution;
	}
}

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
