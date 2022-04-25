#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Numerical.h"

TEST_CASE("Operations\n") {
    Numerical l = Numerical(4);
    Numerical r = Numerical(12.45);

    REQUIRE((l - r) == Numerical(-8.45));
    REQUIRE((l + r) == Numerical(16.45));
    REQUIRE((l / r) == Numerical(0.24316109422));
    REQUIRE((l * r) == Numerical(65.8));

    REQUIRE((r - l) == Numerical(8.45));
    REQUIRE((r / l) == Numerical(3.1125));

    r = Numerical(-2);
    REQUIRE((l - r) == Numerical(6));
    REQUIRE((l + r) == Numerical(2));
    REQUIRE((l / r) == Numerical(-2));
    REQUIRE((l * r) == Numerical(-8));

    REQUIRE((r - l) == Numerical(-6));
    REQUIRE((r / l) == Numerical(-0.5));
}
