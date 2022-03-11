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

Rational    &Rational::operator=(const Rational &other) {
    _numerator = other.getNumerator();
    _denominator = other.getDenominator();
    return *this;
}

Rational    &Rational::operator/=(const Rational &x) {
    // TODO: simplify AND check overflow?
    long long nw_n = _numerator * x.getNumerator();
    long long nw_d = _denominator * x.getDenominator();
    if ((nw_n / _numerator != x.getNumerator()) ||
    (nw_d / _denominator != x.getDenominator())) {
        throw std::overflow_error("Could not perform /= on rational.");
    }
    try {
        ll_factor_gcd(&nw_n, &nw_d);
        _numerator = nw_n;
        _denominator = nw_d;
    }
    catch (std::overflow_error &e) { throw e; }
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
    long long n = getNumerator();
    long long d = getDenominator();

    try {
        ll_factor_gcd(&n, &d);
    }
    catch (std::overflow_error &e) {
        throw e;
    }
}

void    Rational::print()   const {
    printf("%lld/%lld\n", getNumerator(), getDenominator());
}

long long    Rational::getDenominator(void)  const {
    return _denominator;
}

void        Rational::setDenominator(long long n) {
    _denominator = n;
}

long long    Rational::getNumerator(void)    const {
    return _numerator;
}

void        Rational::setNumerator(long long n) {
    _numerator = n;
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

Rational        operator*(const Rational &lhs, const Rational &rhs) {
    long long new_numerator = lhs.getNumerator() * rhs.getNumerator();
    long long new_denom = lhs.getDenominator() * rhs.getDenominator();
    if (new_numerator / lhs.getNumerator() != rhs.getNumerator() ||
    new_denom / lhs.getDenominator() != rhs.getDenominator()) {
        throw std::overflow_error("Could not multiply.");
    }
    return Rational(new_numerator, new_denom);
}

Rational        operator*(const Rational &r, long long n) {
    Rational rn = Rational(n, 1);
    try {
        return (r * rn);
    }
    catch (std::overflow_error &e) { throw e; }
}

Rational        operator+(const Rational &lhs, const Rational &rhs) {
    printf("OPERATOR + RATIONAL\n");
    long long tmp_d = lhs.getDenominator() * rhs.getDenominator();
    long long lhs_factor = tmp_d / lhs.getDenominator();
    long long rhs_factor = tmp_d / rhs.getDenominator();
    long long tmp_ln = lhs.getNumerator() * lhs_factor;
    long long tmp_rn = rhs.getNumerator() * rhs_factor;
    long long tmp_n = tmp_ln + tmp_rn;
    if ((tmp_d / lhs.getDenominator() != rhs.getDenominator()) ||
    (tmp_ln / lhs_factor != lhs.getNumerator())||
    (tmp_rn / rhs_factor != rhs.getNumerator()) ||
    (tmp_n - tmp_ln != tmp_rn)) {
        throw std::overflow_error("Could not add rationals.");
    }
    try {
        ll_factor_gcd(&tmp_n, &tmp_d);
        printf("After adding\n");
        Rational(tmp_n, tmp_d).print();
        return Rational(tmp_n, tmp_d);
    }
    catch (std::overflow_error &e) { throw e; }
}

Rational        operator+(const Rational &r, long long n) {
    Rational rn = Rational(n, 1);
    try {
        return (r + rn);
    }
    catch (std::overflow_error &e) { throw e; }
}

Rational        operator+(long long n, const Rational &r) {
    return (r + n);
}

long double     operator+(const Rational &r, long double n) {
    long double ll_r = r.getNumerator() / r.getDenominator();
    return (ll_r + n);
}

long double     operator+(long double n, const Rational &r) {
    return (r + n);
}

Rational        getGcd(const Rational &lhs, const Rational &rhs) {
    return Rational(std::gcd(lhs.getNumerator(), rhs.getNumerator()), 
    std::lcm(lhs.getDenominator(), rhs.getDenominator()));
}

long long        getGcd(const Rational &r, long double n) {
    return 1;
}

long long      getGcd(long double n, const Rational &r) {
    return getGcd(r, n);
}

Rational        getGcd(const Rational &r, long long n) {
    Rational rn = Rational(n, 1);
    return getGcd(r, rn);
}

Rational        getGcd(long long n, const Rational &r) {
    return getGcd(r, n);
}
