#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "SquareRoot.h"
#include <iomanip>
#include <cmath>

TEST_CASE("SquareRoots", "[SquareRoots]") {
	SECTION ("Creation") {
		SquareRoot r = SquareRoot(125);
		REQUIRE(r.getWhole() == 5);
		REQUIRE((r.getSquareRoot() == 5));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		r = SquareRoot(125.12);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getSquareRoot() == 125.12));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		SquareRoot n = SquareRoot(100);
		REQUIRE(n != r);
		
		r = SquareRoot(-4.15);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getSquareRoot() == 4.15));
		REQUIRE(r.getType() == SquareRoot::Type::imaginary);
	
		r = SquareRoot(100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getSquareRoot() == 1));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		r = SquareRoot(-100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getSquareRoot() == 1));
		REQUIRE(r.getType() == SquareRoot::Type::imaginary);

		r = SquareRoot(17);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getSquareRoot() == 17));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		/* From discriminant */
		r = SquareRoot(Fraction(2, 1, 7));
		REQUIRE(r.getWhole() == Fraction(1, 7));
		REQUIRE((r.getSquareRoot() == 105));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		r = SquareRoot(Fraction(-8, 3, 8));
		REQUIRE(r.getWhole() == Fraction(1, 4));
		REQUIRE((r.getSquareRoot() == 134));
		REQUIRE(r.getType() == SquareRoot::Type::imaginary);

		r = SquareRoot(Fraction(25));
		REQUIRE(r.getWhole() == 5);
		REQUIRE((r.getSquareRoot() == 1));
		REQUIRE(r.getType() == SquareRoot::Type::real);

		r = SquareRoot(-36);
		REQUIRE(r.getWhole() == 6);
		REQUIRE((r.getSquareRoot() == 1));
		REQUIRE(r.getType() == SquareRoot::Type::imaginary);
	}
	SECTION ("Multiplication\n") {
		std::cout << "Fractions\n";
		SquareRoot lhs = SquareRoot(4, 2);
		SquareRoot rhs = SquareRoot(2, 14);

		lhs *= rhs;
		REQUIRE(lhs == SquareRoot(16, 7));

		lhs = SquareRoot(2, -7);
		rhs = SquareRoot(-6, 3);
		SquareRoot res = lhs * rhs;
		REQUIRE(res == SquareRoot(-12, -21));

		lhs = SquareRoot(44);
		rhs = SquareRoot(-3);
		lhs *= rhs;
		REQUIRE(lhs == SquareRoot(2, -33));
	}
	SECTION ("Is floating\n") {
		SquareRoot r = SquareRoot(125.5);

		REQUIRE(r.isFloating());

		r = SquareRoot(15);
		REQUIRE(!r.isFloating());

		r = Rational(Fraction(1, 4));
		REQUIRE(!r.isFloating());
	}
	SECTION ("To long double") {
		SquareRoot r = Rational(Fraction(1, 2));
		long double n = (long double)r;
		std::cout << n << "\n";
		REQUIRE(n == (long double)std::sqrt((long double)0.5));

		r = Rational(Fraction(125));
		n = (long double)r;
		REQUIRE(n == std::pow((long double)125, 0.5));
	}
	SECTION ("To numerical solution\n") {
		SquareRoot r = Rational(Fraction(1, 2));
		REQUIRE(r.getNumericalSolution() == std::sqrt((long double)0.5));

		long double n = 117.1234877;
		r = Rational(n);
		REQUIRE(r.getNumericalSolution() == (long double)std::sqrt(n));

		long double g = -117.1234877;
		r = Rational(g);
		REQUIRE(r.getNumericalSolution() == (std::sqrt(std::abs(g))));

		long long m = 25;
		r = Rational(m);
		REQUIRE(r.getNumericalSolution() == (std::sqrt(m)));
	}
}
