#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "math_helpers.h"
#include "Rational.h"

TEST_CASE("Conversion doubles to rationals", "[Rationals]") {
	long double num = (double)1/3;
	double accuracy = 0.00000000001;
	REQUIRE(doubleToRational(num, accuracy) == Rational(1, 3));
	REQUIRE(doubleToRational(1., accuracy) == Rational(1, 1));
	REQUIRE(doubleToRational(0., accuracy) == Rational(0, 1));
	
	/* NaN check */
	num = std::numeric_limits<long double>::quiet_NaN();
	CHECK_THROWS(doubleToRational(num));

	/* Infinity check */
	num = std::numeric_limits<double>::infinity();
	CHECK_THROWS(doubleToRational(num));

	/* Precision checks */
	REQUIRE(doubleToRational(0.3333333333333333333333333333333, accuracy) == Rational(1, 3));
	REQUIRE(doubleToRational(1.5, accuracy) == Rational(3, 2));
	num = (double)1/6;
	REQUIRE(doubleToRational(num, accuracy) == Rational(1, 6));
	num = (double)2/3;
	REQUIRE(doubleToRational(num, accuracy) == Rational(2, 3));
	REQUIRE(doubleToRational(0.142857, accuracy) == Rational(142857, 1000000));
	REQUIRE(doubleToRational(0.363636363636363636, accuracy) == Rational(4, 11));
	REQUIRE(doubleToRational(0.0001, accuracy) == Rational(1, 10000));
	REQUIRE(doubleToRational(0.000001, accuracy) == Rational(1, 1000000));
	REQUIRE(doubleToRational(0.001, accuracy) == Rational(1, 1000));
	REQUIRE(doubleToRational(0.01, accuracy) == Rational(1, 100));
	REQUIRE(doubleToRational(0.0000000001, accuracy) == Rational(1, 10000000000));
	REQUIRE(doubleToRational(0.00000001, accuracy) == Rational(1, 100000000));

	/* Negative numbers */
	REQUIRE(doubleToRational(-0.01) == Rational(-1, 100));
	REQUIRE(doubleToRational(-0.33) == Rational(-33, 100));

	/* Valid accuracy */
	CHECK_THROWS(doubleToRational(1., 15));
	CHECK_THROWS(doubleToRational(1., -1));
}
