#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "computor.h"

TEST_CASE("Polynomial solutions", "[Polynomials]") {
	SECTION("No solutions\n") {
		/* No meaningful solution to be found, degree too high etc */
		std::string input = GENERATE("x = x", "7+10-8+3=9", "x^3 + 4x^2 +2x =5");
		Equation eq = parse_equation(input);
		eq.simplify();

		CHECK_THROWS(solve_equation(eq));
	}
	SECTION("B is zero\n") {
		/* Answer is just comprised of square root part */
		std::string input = "2x^2+7=0";
		Equation eq = parse_equation(input);
		eq.simplify();
		Solution s = solve_equation(eq);

		REQUIRE((std::string)s == "+/-1/2√14𝑖");

		input = "2x^2+2=0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "+/-𝑖");

		input = "3x^2 = 8";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "+/-2/3√6");
		/* B is zero and discriminant is perfect square */
		input = "2x^2 -2 = 0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "+/-1");
	}
	SECTION("Discriminant is zero\n") {
		/* Answer strictly made up of b part (no sqrt) */
		std::string input = "2x^2 + 4x +2 = 0";
		Equation eq = parse_equation(input);
		eq.simplify();
		Solution s = solve_equation(eq);

		REQUIRE((std::string)s == "-1");
	}
	SECTION("First degree answers\n") {
		std::string input = "2x = 15";
		Equation eq = parse_equation(input);
		eq.simplify();
		Solution s = solve_equation(eq);

		REQUIRE((std::string)s == "7(1/2)");

	}
	SECTION("Second degree answers\n") {
		std::string input = "2x^2+2x-6=0";
		Equation eq = parse_equation(input);
		eq.simplify();
		Solution s = solve_equation(eq);

		REQUIRE((std::string)s == "1/2(√13-1)\n-1/2(1+√13)");
		
		input = "2x^2+2x-4=0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "1\n-2");

		input = "2x^2+2x-2=0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "1/2(√5-1)\n-1/2(1+√5)");

		input = "17x^2+5x-28=0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "1/34(√1929-5)\n-1/34(5+√1929)");

		input = "2X^2 -0.5X + 6 = 0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "1/8𝑖(√191-𝑖)\n-1/8𝑖(𝑖+√191)");

		input = "3X^2 -0.5X + 1.5 = 0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "1/12𝑖(√71-𝑖)\n-1/12𝑖(𝑖+√71)");

		input = "2x^2 + 3x + 1 = 0";
		eq = parse_equation(input);
		eq.simplify();
		s = solve_equation(eq);

		REQUIRE((std::string)s == "-1/2\n-1");
	}
}