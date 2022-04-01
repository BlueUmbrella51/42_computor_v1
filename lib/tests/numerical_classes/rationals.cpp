#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Rational.h"
#include <limits.h>

TEST_CASE("Rationals", "[Rationals]") {
	SECTION("Overflow\n") {
		std::cout << "Testing: Rationals overflow\n";

		long long w = LONG_LONG_MIN;
		long long n = LONG_LONG_MIN;
		CHECK_THROWS(Rational(w, n, 1));
		CHECK_THROWS(Rational(w, n, -1));
		CHECK_THROWS(Rational(-1, n, 1));
		CHECK_THROWS(Rational(w, -1, 1));
		w = LONG_LONG_MAX;
		n = LONG_LONG_MAX;
		CHECK_THROWS(Rational(w, n, 1));
		CHECK_THROWS(Rational(w, 1, 1));
	}
	SECTION("Normal creation\n") {
		std::cout << "Testing: Rationals creation\n";
		long long w = -5;
		long long n = -7;
		long long d = 4;

		Rational r = Rational(w, n, d);
		REQUIRE(r == Rational(-6, 3, 4));

		w = 5;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(3, 1, 4));

		n = 7;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(6, 3, 4));

		w = -1;
		n = 7;
		d = 4;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(-2, 3, 4));

		w = 1;
		n = -7;
		d = 4;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(0, -3, 4));

		w = 0;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(-1, 3, 4));

		w = -8;
		n = -3;
		d = -4;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(-8, 3, 4));

		w = -8;
		n = 3;
		d = -4;
		r = Rational(w, n, d);
		REQUIRE(r == Rational(-8, 3, 4));
	}
	SECTION("Equality operators\n") {
		std::cout << "Testing: Rationals equality checks\n";
		Rational n = Rational(-1, 4, 3);
		Rational m = Rational(1, 4, 3);
		Rational o = n;

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
		std::cout << "Testing: Rationals addition\n";
		Rational r = Rational(5, 7) + 1;
		REQUIRE(r == Rational(1, 5 ,7));

		r = Rational(0, -5, 7) + 1;
		REQUIRE(r == Rational(2, 7));

		r = Rational(1, 7) + Rational(-5, 7);
		REQUIRE(r == Rational(-4, 7));

		r = Rational(-1, 5, 7) + Rational(1, 1, 3);
		REQUIRE(r == Rational(-8, 21));

		r = Rational(2, 3) + Rational(1, 3);
		REQUIRE(r == 1);

		r = Rational(-4, 1, 3) + Rational(3, 2, 3);
		REQUIRE(r == Rational(-2, 3));

		r = Rational(-3, 7) + Rational(-4, 7);
		REQUIRE(r == -1);

		r = Rational(3, 7) + Rational(-4, 7);
		REQUIRE(r == Rational(-1, 7));

		r = Rational(3, 7) + Rational(4, 7);
		REQUIRE(r == 1);

		r = Rational(3, -3, 7) + Rational(-4, 7);
		REQUIRE(r == 2);

		r = Rational(3, -3, 7) + Rational(4, 7);
		REQUIRE(r == Rational(3, 1, 7));

		r = Rational(3, 3, 7) + Rational(8, 4, 7);
		REQUIRE(r == 12);

		r = Rational(3, 3, 7) + Rational(-8, 4, 7);
		REQUIRE(r == Rational(-5, 1, 7));

		r = Rational(3, 1, 21) + Rational(-8, 1, 43);
		REQUIRE(r == Rational(-4, 881, 903));

		r = Rational(3, 1, 21) + Rational(8, 1, 43);
		REQUIRE(r == Rational(11, 64, 903));
	}
	SECTION("Subtraction\n") {
		std::cout << "Testing: Rationals subtraction\n";
		Rational r = 1 - Rational(1, 1, 3);
		REQUIRE(r == Rational(-1, 3));

		r = 0 - Rational(2, 3);
		REQUIRE(r == Rational(-2, 3));

		r -= 5;
		REQUIRE(r == Rational(-5, 2, 3));

		r += 5;
		REQUIRE(r == Rational(-2, 3));

		r /= -2;
		REQUIRE(r == Rational(1, 3));

		r *= -8;
		REQUIRE(r == Rational(-2, 2, 3));

		/* Both negative */
		r = Rational(-7, 2, 3) - Rational(-2, 3);
		REQUIRE(r == -7);

		/* L negative, R positive */
		r = Rational(-7, 2, 3) - Rational(2, 3);
		REQUIRE(r == Rational(-8, 1, 3));

		/* R negative, L positive */
		r = Rational(7, 2, 3) - Rational(-2, 3);
		REQUIRE(r == Rational(8, 1, 3));

		/* R becomes negative */
		r = Rational(1, 2, 3) - Rational(4, 1, 7);
		REQUIRE(r == Rational(-2, 10, 21));

		/* R becomes Positive */
		r = Rational(-1, 2, 3) - Rational(-4, 1, 7);
		REQUIRE(r == Rational(2, 10, 21));

		/* 0 and negative */
		r = 0 - Rational(-2, 3);
		REQUIRE(r == Rational(2, 3));

		/* Negative and 0 */
		r = Rational(-2, 3) - 0;
		REQUIRE(r == Rational(-2, 3));
	}
	SECTION("Division\n") {
		std::cout << "Testing: Rationals division\n";
		/* Both negative */
		Rational r = Rational(-1, 2, 3) / Rational(-4, 1, 7);
		REQUIRE(r == Rational(35, 87));

		/* rhs negative */
		r = Rational(2, 3);
		r /= -2;
		REQUIRE(r == Rational(-1, 3));

		r = Rational(2, 3) / -1;
		REQUIRE(r == Rational(-2, 3));

		r = Rational(4, 1, 8) / Rational(7, 9, 14);
		REQUIRE(r == Rational(231, 428));

		r = Rational(4, 1, 8);
		r /= Rational(2, 9, 14);
		REQUIRE(r == Rational(1, 83, 148));

		CHECK_THROWS(Rational(2, 3) / 0);
	}
	SECTION("Multiplication\n") {
		std::cout << "Testing: Rationals multiplication\n";
		Rational r = Rational(-1, 4);

		r *= 4;
		REQUIRE(r == -1);

		r += Rational(1, 3);
		REQUIRE(r == Rational(-2, 3));

		r *= Rational(2, 4, 5);
		REQUIRE(r == Rational(-1, 13, 15));
		 
		r = Rational(-8, 1, 19) * Rational(7, 7, 8);
		REQUIRE(r == Rational(-63, 63, 152));
	}
	SECTION("Get gcd\n") {
		Rational r = getGcd(Rational(-1, 2), 4);
		REQUIRE(r == Rational(1, 2));

		r = getGcd(Rational(-1, 2), -4);
		REQUIRE(r == Rational(1, 2));
		
		auto n = getGcd(Rational(1, 5), 1.22);
		REQUIRE(n == 1);

		n = getGcd(0.45, Rational(1, 2, 3));
		REQUIRE(n == 1);

		r = getGcd(Rational(1, 3), Rational(1, 4));
		REQUIRE(r == Rational(1, 12));

		r = getGcd(Rational(1, 7), Rational(3, 8));
		REQUIRE(r == Rational(1, 56));

		r = getGcd(Rational(1, 3), 3);
		REQUIRE(r == Rational(1, 3));

		r = getGcd(Rational(1, 3), 7);
		REQUIRE(r == Rational(1, 3));

		r = getGcd(Rational(3), Rational(4));
		REQUIRE(r == Rational(1));

		r = getGcd(Rational(5, 1, 3), Rational(3));
		REQUIRE(r == Rational(1, 3));

		r = getGcd(Rational(5, 1, 3), Rational(3, 7));
		REQUIRE(r == Rational(1, 21));
	}
}
