#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>
#include "Solution.h"
#include "SquareRoot.h"
#include "Rational.h"
#include "Fraction.h"

TEST_CASE("Solutions", "[visualisation of solutions]") {
    SECTION("Precision mode\n")  {
        SECTION("Compound\n") {
            SquareRoot q = SquareRoot(-4);
            CompoundSolutions c = CompoundSolutions(Rational(2), q);
            REQUIRE(std::get<0>(c.toStrings()) == "2𝑖(1-𝑖)");
            REQUIRE(std::get<1>(c.toStrings()) == "-2𝑖(𝑖+1)");

            q = SquareRoot(3);
            c = CompoundSolutions(Rational(2), q);
            REQUIRE(std::get<0>(c.toStrings()) == "2+√3");
            REQUIRE(std::get<1>(c.toStrings()) == "2-√3");

            q = SquareRoot(-3);
            c = CompoundSolutions(Rational(2), q);
            REQUIRE(std::get<0>(c.toStrings()) == "2+√3𝑖");
            REQUIRE(std::get<1>(c.toStrings()) == "2-√3𝑖");

            q = SquareRoot(3) / Rational(Fraction(8, 1));
            c = CompoundSolutions(Fraction(1, 8), q);
            REQUIRE(std::get<0>(c.toStrings()) == "1/8(1+√3)");
            REQUIRE(std::get<1>(c.toStrings()) == "1/8(1-√3)");

            q = SquareRoot(-3) / Rational(Fraction(-8, 1));
            c = CompoundSolutions(Fraction(-1, 8), q);
            REQUIRE(std::get<0>(c.toStrings()) == "-1/8𝑖(√3-𝑖)");
            REQUIRE(std::get<1>(c.toStrings()) == "1/8𝑖(𝑖+√3)");

            q = SquareRoot(-3) / Rational(Fraction(-8, 1));
            c = CompoundSolutions(Fraction(1, 8), q);
            REQUIRE(std::get<0>(c.toStrings()) == "-1/8𝑖(𝑖+√3)");
            REQUIRE(std::get<1>(c.toStrings()) == "-1/8𝑖(𝑖-√3)");

            q = SquareRoot(28);
            c = CompoundSolutions(Rational(4), q);
            REQUIRE(std::get<0>(c.toStrings()) == "2(2+√7)");
            REQUIRE(std::get<1>(c.toStrings()) == "2(2-√7)");

            q = SquareRoot(-28) / Rational(Fraction(-8, 1));
            c = CompoundSolutions(Fraction(4), q);
            REQUIRE(std::get<0>(c.toStrings()) == "-1/4(√7𝑖-16)");
            REQUIRE(std::get<1>(c.toStrings()) == "1/4(16+√7𝑖)");

            /* b == 0 */
            q = SquareRoot(-3);
            c = CompoundSolutions(Rational(0), q);
            REQUIRE(std::get<0>(c.toStrings()) == "+/-√3𝑖");

            q = SquareRoot(3);
            c = CompoundSolutions(Rational(0), q);
            REQUIRE(std::get<0>(c.toStrings()) == "+/-√3");

            q = SquareRoot(16);
            c = CompoundSolutions(Rational(0), q);
            REQUIRE(std::get<0>(c.toStrings()) == "+/-4");

            q = SquareRoot(-16);
            c = CompoundSolutions(Rational(0), q);
            REQUIRE(std::get<0>(c.toStrings()) == "+/-4𝑖");
        }
        SECTION("Simple\n") {
            /* Two purely numerical real solutions */
            SimpleSolutions c = SimpleSolutions(Fraction(2, 3), Fraction(2, 1, 7));

            REQUIRE(std::get<0>(c.toStrings()) == "2(17/21)");
            REQUIRE(std::get<1>(c.toStrings()) == "-1(10/21)");

            c = SimpleSolutions(4, 5);
            REQUIRE(std::get<0>(c.toStrings()) == "9");
            REQUIRE(std::get<1>(c.toStrings()) == "-1");
            
            c = SimpleSolutions(-4, -5);
            REQUIRE(std::get<0>(c.toStrings()) == "-9");
            REQUIRE(std::get<1>(c.toStrings()) == "1");

            c = SimpleSolutions(0.25671871, Fraction(8, 1, 9));
            REQUIRE(std::get<0>(c.toStrings()) == "8.367830");
            REQUIRE(std::get<1>(c.toStrings()) == "7.854392");
            std::cout << "\n"<< c;

            c = SimpleSolutions(16, Fraction(8, 1, 9));
            REQUIRE(std::get<0>(c.toStrings()) == "24(1/9)");
            REQUIRE(std::get<1>(c.toStrings()) == "7(8/9)");
            std::cout << "\n"<< c;

            /* Square root == 0 */
            
        }
    }
}
