#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Root.h"

TEST_CASE("Roots", "[Roots]") {
	SECTION ("Creation") {
		Root r = Root(125);
		REQUIRE(r.getWhole() == 5);
		REQUIRE((r.getRoot() == 5));

		r = Root(125.12);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getRoot() == 125.12));
		Root n = Root(100);
		REQUIRE(n != r);
		
		r = Root(100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getRoot() == 1));

		r = Root(-100);
		REQUIRE(r.getWhole() == 10);
		REQUIRE((r.getRoot() == 1));
		REQUIRE(r.getType() == Root::Type::imaginary);

		r = Root(17);
		REQUIRE(r.getWhole() == 1);
		REQUIRE((r.getRoot() == 17));
	}
	SECTION ("Addition\n") {
		Root lhs = Root(4, 2, 2);
		Root rhs = Root(2, 14, 2);

		lhs *= rhs;
		REQUIRE(lhs == Root(16, 7, 2));
	}
}