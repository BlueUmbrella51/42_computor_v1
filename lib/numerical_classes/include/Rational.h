#ifndef RATIONAL_NUMBER_H
# define RATIONAL_NUMBER_H
#include <math_helpers.h>
#include <iostream>

class Rational {
    // private:
        long long    _numerator;
        long long    _denominator;
        // int                   _sign;
        // Find GCD, divide numerator and denominator by it

    public:
        // Rational(unsigned long long numerator, unsigned long long denominator, int sign);
        Rational();
        // Rational(double n);
        Rational(long long numerator, long long denominator);
        ~Rational();
        Rational    &operator=(const Rational &other);
        void        setDenominator(long long n);
        long long   getDenominator(void)    const;
        void        setNumerator(long long n);
        long long    getNumerator(void)  const;
        Rational    &operator/=(const Rational &x);
        // Rational    add(const Rational &r);
        // Rational    subtract(const Rational &r);
        // Rational    subtract(long int n);
        // Rational    multiply(const Rational &r);
        // Rational    multiply(long int n);
        // Rational    divide(const Rational &r);
        // Rational    divide(long int n);
        // // Rational    exponentiate(long int power);
        // // Decimal exponents HAVE to be turned into rationals
        Rational    exponentiate(const Rational &r);
        void        print() const;
        void        reduce(void);
};

Rational        doubleToRational(long double n, long double accuracy = 0.0);
bool            operator==(const Rational &lhs, const Rational &rhs);
std::ostream    &operator<<(std::ostream &os, const Rational &x);
Rational        operator/(const Rational &lhs, const Rational &rhs);

Rational        operator*(const Rational &lhs, const Rational &rhs);
Rational        operator*(const Rational &r, long long n);

Rational        operator+(const Rational &lhs, const Rational &rhs);
Rational        operator+(const Rational &r, long long n);
Rational        operator+(long long n, const Rational &r);
long double     operator+(const Rational &r, long double n);
long double     operator+(long double n, const Rational &r);

Rational        getGcd(Rational lhs, Rational rhs);
long long       getGcd(Rational r, long double n);
long long       getGcd(long double n, Rational r);
Rational        getGcd(Rational r, long long n);
Rational        getGcd(long long n, Rational r);

#endif
