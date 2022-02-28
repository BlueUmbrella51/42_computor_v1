#ifndef RATIONAL_NUMBER_HPP
# define RATIONAL_NUMBER_HPP
#include <numeric>

class Rational {
    private:
        long int    _numerator;
        long int    _denominator;
        // Find GCD, divide numerator and denominator by it
        void        reduce(void);
    
    public:
        Rational(long int numerator, long int denominator);
        Rational(double n);
        Rational();
        ~Rational();
        void        setDenominator(long int n);
        long int    getDenominator(void)    const;
        void        setNumerator(long int n);
        long int    getNumerator(void)  const;
        Rational	findGcd(Rational r);
        Rational&   operator/=(const Rational &x);
        Rational    operator/(const Rational &x);
        // Rational    add(const Rational &r);
        // Rational    add(long int n);
        // Rational    subtract(const Rational &r);
        // Rational    subtract(long int n);
        // Rational    multiply(const Rational &r);
        // Rational    multiply(long int n);
        // Rational    divide(const Rational &r);
        // Rational    divide(long int n);
        // Rational    exponentiate(long int power);
        // Decimal exponents HAVE to be turned into rationals
        Rational    exponentiate(const Rational &r);
        void        print() const;
};

#endif
