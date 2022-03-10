#include "Rational.h"
// TODO: division by zero and overflow protection

Rational::Rational(long long int numerator, long long int denominator) {
    // TODO: handle 0 denomionator ??
    _numerator = numerator;
    _denominator = denominator;
    // reduce();
}

Rational::Rational() {
    _numerator = 0;
    _denominator = 1;
}

Rational::~Rational() {

}

Rational    &Rational::operator=(Rational other) {
    _numerator = other.getNumerator();
    _denominator = other.getDenominator();
    return *this;
}

Rational    &Rational::operator/=(const Rational &x) {
    _numerator *= x.getDenominator();
    _denominator *= x.getNumerator();
    return *this;
}

Rational        operator/(const Rational &lhs, const Rational &rhs) {
    Rational r = Rational(lhs.getNumerator() * rhs.getDenominator(), 
    lhs.getDenominator() * rhs.getNumerator());
    r.reduce();
    return (r);
}

std::ostream    &operator<<(std::ostream &os, const Rational &x)
{
    long long d = x.getDenominator();
    long long n = x.getNumerator();
    os << n;
    if (n != 0 && d != 1) {
        os << "/" << d;
    }
    return os;
}

bool        operator==(const Rational &lhs, const Rational &rhs) {
    return (lhs.getNumerator() == rhs.getNumerator()
    && lhs.getDenominator() == rhs.getDenominator());
}

void    Rational::reduce(void) {
    long int n = getNumerator();
    long int d = getDenominator();

    long int    gcd = std::gcd(n, d);

    // TODO: better handling / exceptions for inf/nan/zero division
    if (gcd != 0 && gcd != 1) {
        setNumerator(getNumerator() / gcd);
        setDenominator(getDenominator() / gcd);
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

Rational    doubleToRational(long double n, long double accuracy) {
    long long num, denum;
    try {
        std::tuple<long long int, long long int> ratio = doubleToRatio(n, accuracy);
        num = std::get<0>(ratio);
        denum = std::get<1>(ratio);
    }
    catch (std::overflow_error &e) {
        std::cout << e.what();
        throw (e);
    }
	return Rational(num, denum);
}
