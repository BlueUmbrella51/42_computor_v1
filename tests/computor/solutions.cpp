#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "computor.h"

TEST_CASE("Polynomial solutions", "[Polynomials]") {
	SECTION("No solutions\n") {
		std::string input = "x = x";
		eq = parse_equation(input)
		Solution = solve_equation(eq)
	}
}