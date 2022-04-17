#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Fraction.h"
#include <limits.h>

TEST_CASE("Fractions", "[Fractions]") {
	SECTION("Overflow\n") {
		std::cout << "Testing: Fractions overflow\n";

		long long w = LLONG_MIN;
		long long n = LLONG_MIN;
		CHECK_THROWS(Fraction(w, n, 1));
		CHECK_THROWS(Fraction(w, n, -1));
		CHECK_THROWS(Fraction(-1, n, 1));
		CHECK_THROWS(Fraction(w, -1, 1));
		w = LLONG_MAX;
		n = LLONG_MAX;
		CHECK_THROWS(Fraction(w, n, 1));
		CHECK_THROWS(Fraction(w, 1, 1));
	}
	SECTION("Normal creation\n") {
		std::cout << "Testing: Fractions creation\n";
		long long w = -5;
		long long n = -7;
		long long d = 4;

		Fraction r = Fraction(w, n, d);
		REQUIRE(r == Fraction(-6, 3, 4));

		w = 5;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(3, 1, 4));

		n = 7;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(6, 3, 4));

		w = -1;
		n = 7;
		d = 4;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(-2, 3, 4));

		w = 1;
		n = -7;
		d = 4;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(0, -3, 4));

		w = 0;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(-1, 3, 4));

		w = -8;
		n = -3;
		d = -4;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(-8, 3, 4));

		w = -8;
		n = 3;
		d = -4;
		r = Fraction(w, n, d);
		REQUIRE(r == Fraction(-8, 3, 4));
	}
	SECTION("Equality operators\n") {
		std::cout << "Testing: Fractions equality checks\n";
		Fraction n = Fraction(-1, 4, 3);
		Fraction m = Fraction(1, 4, 3);
		Fraction o = n;

		bool a = (n == m);
		REQUIRE(a == false);
		a = (n < m);
		REQUIRE(a == true);
		a = (n == o);
		REQUIRE(a == true);
		a = (n > m);
		REQUIRE(a == false);
		a = (n < 0);
		REQUIRE(a == true);
		a = (m < 4);
		REQUIRE(a == true);
	}
	SECTION("Addition\n") {
		std::cout << "Testing: Fractions addition\n";
		Fraction r = Fraction(5, 7) + 1;
		REQUIRE(r == Fraction(1, 5 ,7));

		r = Fraction(0, -5, 7) + 1;
		REQUIRE(r == Fraction(2, 7));

		r = Fraction(1, 7) + Fraction(-5, 7);
		REQUIRE(r == Fraction(-4, 7));

		r = Fraction(-1, 5, 7) + Fraction(1, 1, 3);
		REQUIRE(r == Fraction(-8, 21));

		r = Fraction(2, 3) + Fraction(1, 3);
		REQUIRE(r == 1);

		r = Fraction(-4, 1, 3) + Fraction(3, 2, 3);
		REQUIRE(r == Fraction(-2, 3));

		r = Fraction(-3, 7) + Fraction(-4, 7);
		REQUIRE(r == -1);

		r = Fraction(3, 7) + Fraction(-4, 7);
		REQUIRE(r == Fraction(-1, 7));

		r = Fraction(3, 7) + Fraction(4, 7);
		REQUIRE(r == 1);

		r = Fraction(3, -3, 7) + Fraction(-4, 7);
		REQUIRE(r == 2);

		r = Fraction(3, -3, 7) + Fraction(4, 7);
		REQUIRE(r == Fraction(3, 1, 7));

		r = Fraction(3, 3, 7) + Fraction(8, 4, 7);
		REQUIRE(r == 12);

		r = Fraction(3, 3, 7) + Fraction(-8, 4, 7);
		REQUIRE(r == Fraction(-5, 1, 7));

		r = Fraction(3, 1, 21) + Fraction(-8, 1, 43);
		REQUIRE(r == Fraction(-4, 881, 903));

		r = Fraction(3, 1, 21) + Fraction(8, 1, 43);
		REQUIRE(r == Fraction(11, 64, 903));
	}
	SECTION("Subtraction\n") {
		std::cout << "Testing: Fractions subtraction\n";
		Fraction r = 1 - Fraction(1, 1, 3);
		REQUIRE(r == Fraction(-1, 3));

		r = 0 - Fraction(2, 3);
		REQUIRE(r == Fraction(-2, 3));

		r -= 5;
		REQUIRE(r == Fraction(-5, 2, 3));

		r += 5;
		REQUIRE(r == Fraction(-2, 3));

		r /= -2;
		REQUIRE(r == Fraction(1, 3));

		r *= -8;
		REQUIRE(r == Fraction(-2, 2, 3));

		/* Both negative */
		r = Fraction(-7, 2, 3) - Fraction(-2, 3);
		REQUIRE(r == -7);

		/* L negative, R positive */
		r = Fraction(-7, 2, 3) - Fraction(2, 3);
		REQUIRE(r == Fraction(-8, 1, 3));

		/* R negative, L positive */
		r = Fraction(7, 2, 3) - Fraction(-2, 3);
		REQUIRE(r == Fraction(8, 1, 3));

		/* R becomes negative */
		r = Fraction(1, 2, 3) - Fraction(4, 1, 7);
		REQUIRE(r == Fraction(-2, 10, 21));

		/* R becomes Positive */
		r = Fraction(-1, 2, 3) - Fraction(-4, 1, 7);
		REQUIRE(r == Fraction(2, 10, 21));

		/* 0 and negative */
		r = 0 - Fraction(-2, 3);
		REQUIRE(r == Fraction(2, 3));

		/* Negative and 0 */
		r = Fraction(-2, 3) - 0;
		REQUIRE(r == Fraction(-2, 3));
	}
	SECTION("Division\n") {
		std::cout << "Testing: Fractions division\n";
		/* Both negative */
		Fraction r = Fraction(-1, 2, 3) / Fraction(-4, 1, 7);
		REQUIRE(r == Fraction(35, 87));

		/* rhs negative */
		r = Fraction(2, 3);
		r /= -2;
		REQUIRE(r == Fraction(-1, 3));

		r = Fraction(2, 3) / -1;
		REQUIRE(r == Fraction(-2, 3));

		r = Fraction(4, 1, 8) / Fraction(7, 9, 14);
		REQUIRE(r == Fraction(231, 428));

		r = Fraction(4, 1, 8);
		r /= Fraction(2, 9, 14);
		REQUIRE(r == Fraction(1, 83, 148));

		CHECK_THROWS(Fraction(2, 3) / 0);
	}
	SECTION("Multiplication\n") {
		std::cout << "Testing: Fractions multiplication\n";
		Fraction r = Fraction(-1, 4);

		r *= 4;
		REQUIRE(r == -1);

		r += Fraction(1, 3);
		REQUIRE(r == Fraction(-2, 3));

		r *= Fraction(2, 4, 5);
		REQUIRE(r == Fraction(-1, 13, 15));
		 
		r = Fraction(-8, 1, 19) * Fraction(7, 7, 8);
		REQUIRE(r == Fraction(-63, 63, 152));
	}
	SECTION("Get gcd\n") {
		Fraction r = getGcd(Fraction(-1, 2), 4);
		REQUIRE(r == Fraction(1, 2));

		r = getGcd(Fraction(-1, 2), -4);
		REQUIRE(r == Fraction(1, 2));
		
		auto n = getGcd(Fraction(1, 5), 1.22);
		REQUIRE(n == 1);

		n = getGcd(0.45, Fraction(1, 2, 3));
		REQUIRE(n == 1);

		r = getGcd(Fraction(1, 3), Fraction(1, 4));
		REQUIRE(r == Fraction(1, 12));

		r = getGcd(Fraction(1, 7), Fraction(3, 8));
		REQUIRE(r == Fraction(1, 56));

		r = getGcd(Fraction(1, 3), 3);
		REQUIRE(r == Fraction(1, 3));

		r = getGcd(Fraction(1, 3), 7);
		REQUIRE(r == Fraction(1, 3));

		r = getGcd(Fraction(3), Fraction(4));
		REQUIRE(r == Fraction(1));

		r = getGcd(Fraction(5, 1, 3), Fraction(3));
		REQUIRE(r == Fraction(1, 3));

		r = getGcd(Fraction(5, 1, 3), Fraction(3, 7));
		REQUIRE(r == Fraction(1, 21));
	}
	SECTION("Casting\n") {
		long double n = (long double)Fraction(-1, 4);
		long double m = (long double)-0.25;

		REQUIRE(n == m);
		
		n = (long double)Fraction(1, 2);
		m = (long double)0.5;
		REQUIRE(n == m);

		n = (long double)Fraction(-125, 1, 2);
		m = (long double)-125.5;
		REQUIRE(n == m);

		n = (long double)Fraction(-1, 2);
		m = (long double)-0.5;
		REQUIRE(n == m);
	}
}
