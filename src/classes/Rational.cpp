#include "headers/Rational.hpp"
#include "../math/headers/math_helpers.hpp"

Rational::Rational(long int numerator, long int denominator) {
    // TODO: handle 0 denomionator ??
    _numerator = numerator;
    _denominator = denominator;
    reduce();
}

Rational::Rational(double n) {
    *this = doubleToRational(n);
}

Rational::Rational() {
    _numerator = 0;
    _denominator = 0;
}

Rational::~Rational() {

}

Rational    &Rational::operator/=(const Rational &x) {
    _numerator *= x.getDenominator();
    _denominator *= x.getNumerator();
    return *this;
}

Rational    Rational::operator/(const Rational &x) {
    print();
    x.print();
    return Rational(getNumerator() * x.getDenominator(), getDenominator() * x.getNumerator());
}

void    Rational::reduce(void) {
    long int n = getNumerator();
    long int d = getDenominator();

    long int    GCD = std::gcd(n, d);

    // TODO: better handling / exceptions for inf/nan/zero division
    if (GCD != 0) {
        setNumerator(getNumerator() / GCD);
        setDenominator(getDenominator() / GCD);
    }
}

void    Rational::print()   const {
    printf("%ld/%ld\n", getNumerator(), getDenominator());
}

long int    Rational::getDenominator(void)  const {
    return _denominator;
}

void        Rational::setDenominator(long int n) {
    _denominator = n;
}

long int    Rational::getNumerator(void)    const {
    return _numerator;
}

void        Rational::setNumerator(long int n) {
    _numerator = n;
}

Rational    Rational::findGcd(Rational r) {
    // TODO: write own gcd / lcm functions? (handle factoring out negative on 
    // highest degree)
    return Rational(std::gcd(getNumerator(), r.getNumerator()), 
    std::lcm(getDenominator(), r.getDenominator()));
}
