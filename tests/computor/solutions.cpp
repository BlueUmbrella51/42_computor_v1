#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "computor.h"

TEST_CASE("Polynomial solutions", "[Polynomials]") {
	SECTION("No solutions\n") {
		std::string input = "x = x";
		Equation eq = parse_equation(input);
		eq.simplify();
		CHECK_THROWS(solve_equation(eq));
	}
	SECTION("B is zero\n") {
		std::string input = "2x^2+7=0";
		Equation eq = parse_equation(input);
		eq.simplify();
		Solution s = solve_equation(eq);

		REQUIRE((std::string)s == "+/-1/2√14𝑖");
	}
}