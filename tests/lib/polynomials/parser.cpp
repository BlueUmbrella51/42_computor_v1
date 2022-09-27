#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Equation.h"

TEST_CASE("Parsing", "[Parsing]") {
	SECTION("Fractions\n") {
		std::string s = "1(1/3)";
		ParseToken pt = getParsingToken(s, true);
		Token t = doParseToken(pt);
		Fraction r = Fraction(1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/-3)";
		pt = getParsingToken(s, true);
		t = doParseToken(pt);
		r = Fraction(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-1(-1/3)";
		pt = getParsingToken(s, true);
		t = doParseToken(pt);
		r = Fraction(-1, 1, 3);
		REQUIRE(t == Token(r, 0));

		s = "-11/3";
		pt = getParsingToken(s, true);
		t = doParseToken(pt);
		r = Fraction(-3, 2, 3);
		REQUIRE(t == Token(r, 0));
	}
	SECTION("Decimals\n") {
		std::string s = "1.12";
		ParseToken pt = getParsingToken(s, true);
		Token t = doParseToken(pt);
		REQUIRE(t == Token(Fraction(1, 3, 25), 0));

		s = "-131.415";
		pt = getParsingToken(s, true);
		t = doParseToken(pt);
		REQUIRE(t == Token(Fraction(-131, 83, 200), 0));

		s = "-0.5";
		pt = getParsingToken(s, false);
		t = doParseToken(pt);
		REQUIRE(t == Token(Fraction(-1, 2)));
	}
	// No equals
	SECTION("Full inputs") {
		std::string input = "X + 12 - 13X";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "-2(1/2)X^2=-5=";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input= "7+10-8+3=9";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input= "7+10-8+3=9+0x+0x^2+0x^3";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "-2(1/2)=X^2=-5";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "-2(1/2)X^2===-5";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "=-2(1/2)X^2-5";
		CHECK_THROWS(doParseEquation(input));
	
		errno = 0;
		input = "X + 12 - 13X = 2X^2";
		CHECK_NOTHROW(doParseEquation(input));

		// Invalid operation
		errno = 0;
		input = "3X - 14 * 12 = X";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "3X - 14 + 12 = X";
		CHECK_NOTHROW(doParseEquation(input));

		// Invalid indiscriminant
		errno = 0;
		input = "3A - 14 + 12 = X";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "3X - 14 + 12 = X";
		CHECK_NOTHROW(doParseEquation(input));

		// Invalid decimal
		errno = 0;
		input = "X +12. -1 = 4";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "X +12.4 -1 = 4";
		CHECK_NOTHROW(doParseEquation(input));

		// Random token at end
		errno = 0;
		input = "X +12.4 -1 = 4%";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "X +12.4 -1 = 4";
		CHECK_NOTHROW(doParseEquation(input));

		/* Random tests */
		errno = 0;
		input = "X + X + X = X";
		CHECK_NOTHROW(doParseEquation(input));

		/* Invalid degree */
		errno = 0;
		input = "X-2=3X+5X^289178917891789178917";
		CHECK_THROWS(doParseEquation(input));

		/* Negative power is not allowed */
		errno = 0;
		input = "2X^2 + X^-1 = 0";
		CHECK_THROWS(doParseEquation(input));

		errno = 0;
		input = "X-2+2X^2=3X+5X^2-7+4X";
		CHECK_NOTHROW(doParseEquation(input));
	}
	SECTION("Equation simplification\n") {
		errno = 0;
		std::string input = "X-2+2X^2=3X+5X^2-7+4X";
		Equation eq = doParseEquation(input);
		eq.simplify();
		REQUIRE((std::string)eq == "3X² + 6X - 5 = 0");

		input = "3X^2 + 2X^4 + 3X^17 + 56 - 8X = 18X - 2X^2 + 3X^17 + 2X^4";
		eq = doParseEquation(input);
		eq.simplify();
		REQUIRE((std::string)eq == "5X² - 26X + 56 = 0");
	}
}
