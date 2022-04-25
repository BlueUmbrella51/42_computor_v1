#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "computor.h"

TEST_CASE("Polynomial solutions", "[Polynomials]") {
	SECTION("No solutions\n") {
		/* No meaningful solution to be found, degree too high etc */
		std::string input = GENERATE("x = x", "7+10-8+3=9", "x^3 + 4x^2 +2x =5");
		Equation eq = doParseEquation(input);
		eq.simplify();

		CHECK_THROWS(solve_equation(eq));
	}
	SECTION("Precision mode\n") {
		SECTION("B is zero\n") {
			/* Answer is just comprised of square root part */
			std::string input = "2x^2+7=0";
			Equation eq = doParseEquation(input);
			eq.simplify();
			Solution s = solve_equation(eq);

			REQUIRE((std::string)s == "+/-1/2√14𝑖");

			input = "2x^2+2=0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "+/-𝑖");

			input = "3x^2 = 8";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "+/-2/3√6");
			/* B is zero and discriminant is perfect square */
			input = "2x^2 -2 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "+/-1");
		}
		SECTION("Discriminant is zero\n") {
			/* Answer strictly made up of b part (no sqrt) */
			std::string input = "2x^2 + 4x +2 = 0";
			Equation eq = doParseEquation(input);
			eq.simplify();
			Solution s = solve_equation(eq);

			REQUIRE((std::string)s == "-1");
		}
		SECTION("Discriminant and left zero\n") {
			std::string input = "2x^2= 0";
			Equation eq = doParseEquation(input);
			eq.simplify();
			Solution s = solve_equation(eq);

			REQUIRE((std::string)s == "0");
		}
		SECTION("First degree answers\n") {
			std::string input = "2x = 15";
			Equation eq = doParseEquation(input);
			eq.simplify();
			Solution s = solve_equation(eq);
			REQUIRE((std::string)s == "7(1/2)");

			input = "-8x = -19";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "2(3/8)");

			input = "-8x = 19";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "-2(3/8)");
		}
		SECTION("Second degree answers\n") {
			std::string input = "2x^2+2x-6=0";
			Equation eq = doParseEquation(input);
			eq.simplify();
			Solution s = solve_equation(eq);

			REQUIRE((std::string)s == "1/2(√13-1)\n-1/2(1+√13)");
			
			input = "2x^2+2x-4=0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "1\n-2");

			input = "2x^2+2x-2=0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "1/2(√5-1)\n-1/2(1+√5)");

			input = "17x^2+5x-28=0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "1/34(√1929-5)\n-1/34(5+√1929)");

			input = "2X^2 -0.5X + 6 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "1/8𝑖(√191-𝑖)\n-1/8𝑖(𝑖+√191)");

			input = "3X^2 -0.5X + 1.5 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "1/12𝑖(√71-𝑖)\n-1/12𝑖(𝑖+√71)");

			input = "2x^2 + 3x + 1 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);

			REQUIRE((std::string)s == "-1/2\n-1");

			input = "135.78X^2 - 0.5X + 897.321 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "1/67890(125+2√7614886430𝑖)\n1/67890(125-2√7614886430𝑖)");
		
			input = "0.75X^2 - 0.5X + 16.2 = 0";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "1/15(5+√4835𝑖)\n1/15(5-√4835𝑖)");

			input = "-2(1/2)X^2=5";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "+/-√2𝑖");

			input = "-2(1/2)X^2=-5";
			eq = doParseEquation(input);
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "+/-√2");
		}
	}
	SECTION("Numeric mode\n") {
		SECTION("Second degree\n") {
			std::string input = "135.78X^2 - 0.5X + 897.321 = 0";
			Equation eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			Solution s = solve_equation(eq);
			REQUIRE((std::string)s == "0.001841+2.570727𝑖\n0.001841-2.570727𝑖");

			input = "0.75X^2 - 0.5X + 16.2 = 0";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "0.333333+4.635611𝑖\n0.333333-4.635611𝑖");
		
			input = "135.78X^2 + 0.5X + 897.321 = 0";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "2.570727𝑖-0.001841\n-0.001841-2.570727𝑖");

			input = "2X^2 + 2X = 6";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "1.302776\n-2.302776");

			input = "2X^2 + 2X = 0";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "0\n-1");

			input = "-2X^2 + 2(1/2)X  = 0";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "1.250000\n0");

			input = "-2(1/2)X^2=5";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "+/-1.414214𝑖");

			input = "-2(1/2)X^2=-5";
			eq = doParseEquation(input);
			eq.toNumerical();
			eq.simplify();
			s = solve_equation(eq);
			REQUIRE((std::string)s == "+/-1.414214");
		}
	}
}