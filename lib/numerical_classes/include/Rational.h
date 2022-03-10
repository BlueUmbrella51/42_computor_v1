#ifndef RATIONAL_NUMBER_H
# define RATIONAL_NUMBER_H
#include <numeric>
#include <math_helpers.h>
#include <iostream>

class Rational {
    // private:
        unsigned long long    _numerator;
        unsigned long long    _denominator;
        // int                   _sign;
        // Find GCD, divide numerator and denominator by it

    public:
        // Rational(unsigned long long numerator, unsigned long long denominator, int sign);
        Rational();
        // Rational(double n);
        Rational(long long int numerator, long long int denominator);
        ~Rational();
        Rational&   operator=(Rational other);
        void        setDenominator(long int n);
        long int    getDenominator(void)    const;
        void        setNumerator(long int n);
        long int    getNumerator(void)  const;
        Rational	findGcd(Rational r);
        Rational    &operator/=(const Rational &x);
        Rational    add(const Rational &r);
        Rational    add(long int n);
        Rational    subtract(const Rational &r);
        Rational    subtract(long int n);
        Rational    multiply(const Rational &r);
        Rational    multiply(long int n);
        Rational    divide(const Rational &r);
        Rational    divide(long int n);
        // Rational    exponentiate(long int power);
        // Decimal exponents HAVE to be turned into rationals
        Rational    exponentiate(const Rational &r);
        void        print() const;
        void        reduce(void);
};

Rational        doubleToRational(long double n, long double accuracy = 0.0);
bool            operator==(const Rational &lhs, const Rational &rhs);
std::ostream    &operator<<(std::ostream &os, const Rational &x);
Rational        operator/(const Rational &lhs, const Rational &rhs);

#endif
