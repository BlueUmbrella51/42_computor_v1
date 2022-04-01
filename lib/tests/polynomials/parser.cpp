#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Equation.h"

TEST_CASE("Parsing", "[Parsing]") {
	SECTION("Fractions\n") {
		std::string s = "1(1/3)";
		ParseToken pt = getParsingToken(s, true);
		Token t = parse_token(pt);
		Rational r = Rational(1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/-3)";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Rational(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/3)";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Rational(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-11/3";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		r = Rational(-3, 2, 3);
		REQUIRE(t == Token(r, 0));
	}
	SECTION("Decimals\n") {
		std::string s = "1.12";
		ParseToken pt = getParsingToken(s, true);
		Token t = parse_token(pt);
		REQUIRE(t == Token(Rational(1, 3, 25), 0));

		s = "131.415";
		pt = getParsingToken(s, true);
		t = parse_token(pt);
		REQUIRE(t == Token(Rational(131, 83, 200), 0));
	}
	// No equals
	std::string input = "X + 12 - 13X";
	CHECK_THROWS(parse_equation(input));
	input = "X + 12 - 13X = 2X^2";
	CHECK_NOTHROW(parse_equation(input));

	// Invalid operation
	input = "3X - 14 * 12 = X";
	CHECK_THROWS(parse_equation(input));
	input = "3X - 14 + 12 = X";
	CHECK_NOTHROW(parse_equation(input));

	// Invalid indiscriminant
	input = "3A - 14 + 12 = X";
	CHECK_THROWS(parse_equation(input));
	input = "3X - 14 + 12 = X";
	CHECK_NOTHROW(parse_equation(input));

	// Invalid decimal
	input = "X +12. -1 = 4";
	CHECK_THROWS(parse_equation(input));
	input = "X +12.4 -1 = 4";
	CHECK_NOTHROW(parse_equation(input));

	// Random token at end
	input = "X +12.4 -1 = 4%";
	CHECK_THROWS(parse_equation(input));
	input = "X +12.4 -1 = 4";
	CHECK_NOTHROW(parse_equation(input));

	/* Random tests */
	input = "X + X + X = X";
	CHECK_NOTHROW(input);
}
