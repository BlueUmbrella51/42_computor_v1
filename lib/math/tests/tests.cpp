#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "math_helpers.h"
#include "Rational.h"

TEST_CASE("Conversion doubles to rationals", "[Rationals]") {
	double num = (double)1/3;
	Rational n = doubleToRational(num);
	REQUIRE(n.getNumerator() == 1);
	REQUIRE(n.getDenominator() == 3);
}
