#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Root.h"
#include <iomanip>

TEST_CASE("Roots", "[Roots]") {
	SECTION ("Creation") {
		Root r = Root(125);
		REQUIRE(r.getWhole() == 5);
		REQUIRE((r.getRoot() == 5));
		REQUIRE(r.getType() == Root::Type::real);

		r = Root(125.12);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getRoot() == 125.12));
		REQUIRE(r.getType() == Root::Type::real);

		Root n = Root(100);
		REQUIRE(n != r);
		
		r = Root(-4.15);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getRoot() == 4.15));
		REQUIRE(r.getType() == Root::Type::imaginary);
	
		r = Root(100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getRoot() == 1));
		REQUIRE(r.getType() == Root::Type::real);

		r = Root(-100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getRoot() == 1));
		REQUIRE(r.getType() == Root::Type::imaginary);

		r = Root(17);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getRoot() == 17));
		REQUIRE(r.getType() == Root::Type::real);

		/* From discriminant */
		r = Root(Fraction(2, 1, 7));
		REQUIRE(r.getWhole() == Fraction(1, 7));
		REQUIRE((r.getRoot() == 105));
		REQUIRE(r.getType() == Root::Type::real);

		r = Root(Fraction(-8, 3, 8));
		REQUIRE(r.getWhole() == Fraction(1, 4));
		REQUIRE((r.getRoot() == 134));
		REQUIRE(r.getType() == Root::Type::imaginary);

		r = Root(Fraction(25));
		REQUIRE(r.getWhole() == 5);
		REQUIRE((r.getRoot() == 1));
		REQUIRE(r.getType() == Root::Type::real);

		r = Root(-36);
		REQUIRE(r.getWhole() == 6);
		REQUIRE((r.getRoot() == 1));
		REQUIRE(r.getType() == Root::Type::imaginary);
	}
	SECTION ("Multiplication\n") {
		std::cout << "Fractions\n";
		Root lhs = Root(4, 2, 2);
		Root rhs = Root(2, 14, 2);

		lhs *= rhs;
		REQUIRE(lhs == Root(16, 7, 2));
	}
	SECTION ("Is floating\n") {
		Root r = 125.5;

		REQUIRE(r.isFloating());

		r = 15;
		REQUIRE(!r.isFloating());

		r = Rational(Fraction(1, 4));
		REQUIRE(!r.isFloating());

		long double n = (long double)r;
		REQUIRE(n == 0.5);

		r = Rational(Fraction(125));
		n = (long double)r;
		REQUIRE(n == (long double)std::pow(125, 0.5));
	}
}
