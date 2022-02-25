#include "headers/Rational.hpp"
#include "../math/headers/math_helpers.hpp"

Rational::Rational(long int numerator, long int denominator) {
    printf("Num: %ld, Denom: %ld\n", numerator, denominator);
    // TODO: handle 0 denomionator ??
    _numerator = numerator;
    _denominator = denominator;
    reduce();
}

Rational::~Rational() {

}

void    Rational::reduce(void) {
    long int n = getNumerator();
    long int d = getDenominator();

    long int    GCD = std::gcd(n, d);
    printf("GCD %ld\n", GCD);

    setNumerator(getNumerator() / GCD);
    setDenominator(getDenominator() / GCD);
}

void    Rational::print() {
    printf("%ld/%ld\n", getNumerator(), getDenominator());
}

long int    Rational::getDenominator(void) {
    return _denominator;
}

void        Rational::setDenominator(long int n) {
    _denominator = n;
}

long int    Rational::getNumerator(void) {
    return _numerator;
}

void        Rational::setNumerator(long int n) {
    _numerator = n;
}
