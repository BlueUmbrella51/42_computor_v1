#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "math_helpers.h"
#include "Fraction.h"
#include <limits.h>

TEST_CASE("Conversion doubles to ratios", "[Math]") {
	double accuracy = 0.00000000001;

	SECTION("Inputs with no decimal part\n") {
		long double num = GENERATE(-1, 0, 1, 15, LLONG_MAX, LLONG_MIN);
		std::cout << "Testing: inputs with no decimal part " << num << "\n";
		auto [ w, n, d ] = doubleToRatio(num, accuracy);
		REQUIRE(w == num);
		REQUIRE(n == 0);
		REQUIRE(d == 1);
	}

	SECTION("Invalid inputs: NaN and INF\n") {
		std::cout << "Testing: invalid inputs for numerical part " << "\n";
		auto num = std::numeric_limits<long double>::quiet_NaN();
		CHECK_THROWS(doubleToRatio(num));

		/* Infinity check */
		num = std::numeric_limits<double>::infinity();
		CHECK_THROWS(doubleToRatio(num));
	}
	SECTION("Invalid accuracy inputs\n") {
		/* Valid accuracy */
		double num = GENERATE(2., -0.5f, -1.);
		std::cout << "Testing: invalid accuracy throws " << num << "\n";
		CHECK_THROWS(doubleToRatio(1.12, num));
	}
	SECTION("Overflow errors\n") {
		/* Too large to process with precision 0 */
		long double num = GENERATE(LDBL_MAX, LDBL_MIN, 
		(long double)(LLONG_MIN) - 1, (long double)(LLONG_MAX) + 1);
		std::cout << "Testing: input too large to process " << num << "\n";
		CHECK_THROWS(doubleToRatio(num, 0));
	}
	SECTION("Check desired output decimal part for exact doubles with default accuracy\n") {
		auto n_in = 1;
		auto d_in = GENERATE(range(2, 99));
		std::cout << "Testing: desired output for simple fractions " << n_in << "/" << d_in << "\n";
		auto input = (long double)n_in/(long double)d_in;
		auto [w, n, d] = doubleToRatio(input);
		REQUIRE(w == 0);
		REQUIRE(n == n_in);
		REQUIRE(d == d_in);
	}
	SECTION("Base 10 decimal parts\n") {
		auto n_in = 1;
		long long d_in = GENERATE(10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000);
		std::cout << "Testing: desired output for base 10 fractions " << n_in << "/" << d_in << "\n";
		auto input = (long double)n_in/(long double)d_in;
		auto [w, n, d] = doubleToRatio(input, 0);
		REQUIRE(w == 0);
		REQUIRE(n == n_in);
		REQUIRE(d == d_in);
	}
	SECTION("Negative numbers with whole and fractional\n") {
		auto input = -5.5;
		std::cout << "Testing: desired output negative numbers with whole parts " << input << "\n";
		auto [w, n, d] = doubleToRatio(input, 0);
		REQUIRE(w == -5);
		REQUIRE(n == -1);
		REQUIRE(d == 2);

		auto input_1 = -2.75;
		std::cout << "Testing: desired output negative numbers with whole parts " << input_1 << "\n";
		auto [w_1, n_1, d_1] = doubleToRatio(input_1, 0);
		REQUIRE(w_1 == -2);
		REQUIRE(n_1 == -3);
		REQUIRE(d_1 == 4);

		auto input_2 = -0.5;
		std::cout << "Testing: desired output negative numbers with whole parts " << input_2 << "\n";
		auto [w_2, n_2, d_2] = doubleToRatio(input_2, 0);
		REQUIRE(w_2 == 0);
		REQUIRE(n_2 == -1);
		REQUIRE(d_2 == 2);
	}
	SECTION("Primes\n") {
		bool is_prime = isPrime(64144081);
		REQUIRE(is_prime == false);

		auto n = findNextPrime(2);
		REQUIRE(n == 3);
	}
}
