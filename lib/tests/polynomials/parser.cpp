#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Equation.h"

TEST_CASE("Parsing", "[Parsing]") {
	SECTION("Fractions\n") {
		std::string s = "1(1/3)";
		ParseToken pt = getParsingToken(s, true);
		Token t = parse_token(pt);
		Fraction r = Fraction(1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/-3)";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Fraction(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/3)";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Fraction(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-11/3";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Fraction(-3, 2, 3);
		REQUIRE(t == Token(r, 0));
	}
	SECTION("Decimals\n") {
		std::string s = "1.12";
		ParseToken pt = getParsingToken(s, true);
		Token t = parse_token(pt);
		REQUIRE(t == Token(Fraction(1, 3, 25), 0));

		s = "-131.415";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		REQUIRE(t == Token(Fraction(-131, 83, 200), 0));

		s = "-0.5";
		pt = getParsingToken(s, false);
		t = parse_token(pt);
		REQUIRE(t == Token(Fraction(-1, 2)));
	}
	// No equals
	SECTION("Full inputs") {
		std::string input = "X + 12 - 13X";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "X + 12 - 13X = 2X^2";
		CHECK_NOTHROW(parse_equation(input));

		// Invalid operation
		errno = 0;
		input = "3X - 14 * 12 = X";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "3X - 14 + 12 = X";
		CHECK_NOTHROW(parse_equation(input));

		// Invalid indiscriminant
		errno = 0;
		input = "3A - 14 + 12 = X";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "3X - 14 + 12 = X";
		CHECK_NOTHROW(parse_equation(input));

		// Invalid decimal
		errno = 0;
		input = "X +12. -1 = 4";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "X +12.4 -1 = 4";
		CHECK_NOTHROW(parse_equation(input));

		// Random token at end
		errno = 0;
		input = "X +12.4 -1 = 4%";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "X +12.4 -1 = 4";
		CHECK_NOTHROW(parse_equation(input));

		/* Random tests */
		errno = 0;
		input = "X + X + X = X";
		CHECK_NOTHROW(parse_equation(input));

		/* Invalid degree */
		errno = 0;
		input = "X-2=3X+5X^289178917891789178917";
		CHECK_THROWS(parse_equation(input));

		/* Negative power is not allowed */
		errno = 0;
		input = "2X^2 + X^-1 = 0";
		CHECK_THROWS(parse_equation(input));

		errno = 0;
		input = "X-2+2X^2=3X+5X^2-7+4X";
		CHECK_NOTHROW(parse_equation(input));
	}
	SECTION("Equation simplification\n") {
		errno = 0;
		std::string input = "X-2+2X^2=3X+5X^2-7+4X";
		Equation eq = parse_equation(input);
		eq.simplify();
		REQUIRE((std::string)eq == "3X² + 6X - 5 = 0");

		input = "3X^2 + 2X^4 + 3X^17 + 56 - 8X = 18X - 2X^2 + 3X^17 + 2X^4";
		eq = parse_equation(input);
		eq.simplify();
		REQUIRE((std::string)eq == "5X² - 26X + 56 = 0");
	}
}
