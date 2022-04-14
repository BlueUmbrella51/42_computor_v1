#include "computor.h"
#include "SquareRoot.h"
#include "Solution.h"
#include <iomanip>

void		solve_first_degree(Equation &eq) {
	/* Form: 2X = 4. 
	If ax = 0, X has to be 0. In all other cases, subtract or add 
	coefficient of degree 0 from both sides, then divide both sides
	by coefficient of degree 1. */
	auto t = eq.findTokenOfDegree(eq.getEquationLeft(), 0);
	auto t1 = eq.findTokenOfDegree(eq.getEquationLeft(), 1);

	if (!t) {
		// Token found
		std::cout << "Solution:\nX = 0.\n";
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
		std::cout << "Solution:\nX = " << sol.value()  << ".\n";
	}
}

void		solve_second_degree(Equation &eq) {
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
	Rational divisor = (2 * a);
	Rational left = -b / divisor;
	SquareRoot right = SquareRoot(discriminant) / divisor;

	std::cout << "Discriminant: " << discriminant << "SquareRoot discriminant: " << SquareRoot(discriminant) <<"\nLeft: " << left << "\nRight: " << right << "\n";
	if (discriminant != 0) {
		if (discriminant > 0) {
			std::cout << "Discriminant is strictly positive.\n";
		}
		else {
			std::cout << "Discriminant is strictly negative.\n";
		}
		Solution s = Solution(left, right);

		std::cout << "Solutions:\n" << s << "\n";
	}
	else {
		std::cout << "Solution:\n" << left;
	}
}

void		solve_equation(Equation &eq) {
	int		highest_degree = eq.getHighestDegree();

	if (eq.getEquationLeft().empty()) {
		throw std::invalid_argument("Equation given when simplified comes down to \"0 = 0\", cannot solve.");
	}
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
