#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Numerical.h"

TEST_CASE("Operations\n") {
    Numerical l = Numerical(4);
    Numerical r = Numerical(12.45);

    REQUIRE((l - r) == Numerical(-8.45));
    REQUIRE((l + r) == Numerical(16.45));
    REQUIRE((l * r) == Numerical(49.8));

    REQUIRE((r - l) == Numerical(8.45));
    REQUIRE((r / l) == Numerical(3.1125));

    r = Numerical(-2.0);
    REQUIRE((l - r) == Numerical(6));
    REQUIRE((l + r) == Numerical(2));
    REQUIRE((l / r) == Numerical(-2));
    REQUIRE((l * r) == Numerical(-8));

    REQUIRE((r - l) == Numerical(-6));
    REQUIRE((r / l) == Numerical(-0.5));

    Numerical n = std::numeric_limits<long double>::max();
    Numerical m = 10.25;

    std::feclearexcept(FE_ALL_EXCEPT);
    CHECK_THROWS(n * m);

    n = std::numeric_limits<long double>::max();
    std::feclearexcept(FE_ALL_EXCEPT);
    CHECK_THROWS(n + n);       
    
    n = std::numeric_limits<long double>::min();
    m = 10.0;
    std::feclearexcept(FE_ALL_EXCEPT);
    CHECK_THROWS(n / m);
    // 	SECTION("Overflow checks\n") {
	// 	long double n = std::numeric_limits<long double>::max();

	// 	REQUIRE(!multiplicationExceedsLimits(n, 1));
	// 	REQUIRE(multiplicationExceedsLimits(n, 10.25));
	// 	REQUIRE(!multiplicationExceedsLimits(n, 0.5f));
	// 	REQUIRE(!multiplicationExceedsLimits(-6.0f, 8));

	// 	n = std::numeric_limits<long double>::lowest();
	// 	REQUIRE(!subtractionExceedsLimits(n, -1));
	// 	REQUIRE(!subtractionExceedsLimits(15.0f, 20.25f)); 

	// 	n = std::numeric_limits<long double>::min();
	// 	REQUIRE(divisionExceedsLimits(n, 10.0f));
	// 	REQUIRE(!divisionExceedsLimits(1289718971.8971897, 8971.871));

	// 	n = std::numeric_limits<long double>::max();
	// 	REQUIRE(additionExceedsLimits(n, n));
	// 	REQUIRE(!additionExceedsLimits(123871.8718971, 89718971.858));
	// }
}
