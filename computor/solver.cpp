#include "computor.h"
#include "SquareRoot.h"
#include "Solution.h"

Solution		solve_first_degree(Equation &eq) {
	/* Form: 2X = 4. */

	Rational coeffDegrZero = eq.findCoeffOfDegree(eq.getEquationLeft(), 0);
	Rational coeffDegrOne = eq.findCoeffOfDegree(eq.getEquationLeft(), 1);

	return Solution(-coeffDegrZero / coeffDegrOne);
}

Solution		solve_second_degree(Equation &eq) {
	auto a_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 2));
	auto b_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 1));
	auto c_token = (eq.findTokenOfDegree(eq.getEquationLeft(), 0));

	Rational a = a_token ? a_token.value().getCoeff(): Rational(0);
	Rational b = b_token ? b_token.value().getCoeff(): Rational(0);
	Rational c = c_token ? c_token.value().getCoeff(): Rational(0);
	
	Rational discriminant = (b * b) - (4 * a * c);
	std::cout << "Discriminant: " << discriminant << "\n";
	Rational divisor = (2 * a);
	Rational left = -b / divisor;

	if (left == (long long)left) {
		left = (long long)left;
	}
	if (discriminant > 0) {
		std::cout << "Discriminant is strictly positive.\n";
	}
	else if (discriminant < 0) {
		std::cout << "Discriminant is strictly negative.\n";
	}
	else {
		std::cout << "Discriminant is zero.\n";
	}
	SquareRoot right = SquareRoot(discriminant) / divisor;
	return Solution(left, right);
}

Solution		solve_equation(Equation &eq) {
	int		highest_degree = eq.getHighestDegree();
	Solution s;

	if (eq.getEquationLeft().empty() && eq.hasZeroDegreeTokens()) {
		throw std::invalid_argument("Equation given when simplified comes down to \"0 = 0\", which is always true. Therefor all legal values of X are a solution.");
	}
	if (eq.getHighestDegree() == 0) {
		throw std::invalid_argument("Equation comes down to comparison of two constants, no solutions exist.");
	}
	else if (highest_degree == 1) {
		s = solve_first_degree(eq);
	}
	else if (highest_degree == 2) {
		s = solve_second_degree(eq);
	}
	else {
		throw std::invalid_argument("The polynomial degree is strictly greater than two, cannot solve.");
	}
	return s;
}
