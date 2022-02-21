#ifndef RATIONAL_NUMBER_HPP
# define RATIONAL_NUMBER_HPP

class Rational {
    private:
        long int  _numerator;
        long int  _denominator;
    
    public:
        Rational(long int numerator, long int denominator);
        ~Rational();
}

#endif