#include "Rational.h"
#include <numeric>
#include <iostream>
#include <tuple>
#include <assert.h>
#include <limits.h>

Rational::Rational():
_n{0}, _d{1}, _w{0} {

}

Rational::Rational(long long n, long long d):
_n{n}, _d{d}, _w{0} {
	assert(d != 0);
	simplify();
}

Rational::Rational(long long n, long long d, long long w) :
_n{n}, _d{d}, _w{w} {
	assert(d != 0);
	simplify();
}

Rational::Rational(const Rational &rhs) :
_n{ rhs._n }, _d{rhs._d}, _w{rhs._w} {

}

Rational 	&Rational::operator-() {
	// If relevant part is long long min, we can't make it positive
	if (_w != 0) {
		assert(_w != LONG_LONG_MIN);
		_w *= -1;
	}
	else {
		assert(_n != LONG_LONG_MIN);
		_n *= -1;
	}
	return *this;
}

Rational	&Rational::operator=(const Rational &rhs) {
	if (this != &rhs) {
		this->_n = rhs._n;
		this->_d = rhs._d;
		this->_w = rhs._w;
	}
	return *this;
}

bool		Rational::operator==(const Rational &rhs) const {
	/* Returns true for equivalence, so 1(1/2) == 1(3/6) returns true */
	return (_w == rhs._w && (_n * rhs._d) == (rhs._n * _d));
}

bool		Rational::operator!=(const Rational &rhs) const {
	return !(*this == rhs);
}

bool		Rational::operator>(const Rational &rhs) const {
	if (_w > rhs._w) { return true; }
	if (_w < rhs._w) {return false; }
	return ((_n * rhs._d) > (rhs._n * _d));
}

bool		Rational::operator>=(const Rational &rhs) const {
	return (*this > rhs || *this == rhs);
}

bool		Rational::operator<(const Rational &rhs) const {
	if (_w < rhs._w) { return true; }
	else { return ((_n * rhs._d) < (rhs._n * _d)); }
}

bool		Rational::operator<=(const Rational &rhs) const {
	return (*this < rhs || *this == rhs);
}

Rational	&Rational::operator+=(const Rational &rhs){
	// a += b
	if (*this == 0) {
		*this = rhs;
	}
	else if (*this < 0 && rhs >= 0) {
		/* 	If a < 0 and b >= 0: -a + b == b - abs(a) */
		*this = rhs - *this;
	}
	else if (rhs < 0) {
		/* a + - b == a - abs(b)*/
		*this -= abs(rhs);
	}
	else {
		/* Both a and b >= 0 */
		// Calculate new whole part
		/* Prevent overflow */
		assert(!additionExceedsLimits(_w, rhs._w));
		long long nw_w = _w + rhs._w;
		
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactors(_d, rhs._d);

		/* Prevent multiplication overflow (factors and numerators are guaranteed to be positive) */
		assert(!multiplicationExceedsLimits(_n, factor_left) 
		&& !multiplicationExceedsLimits(rhs._n, factor_right)
		&& !additionExceedsLimits((_n * factor_left), (rhs._n * factor_right)));
		long long nw_n = (_n * factor_left) + (rhs._n * factor_right);
		long long nw_d = lcm;

		_w = nw_w;
		_n = nw_n;
		_d = nw_d;
		simplify();
	}
	return *this;
}

Rational	&Rational::operator-=(const Rational &rhs) {
	if (*this == 0) {
		*this = rhs;
		-(*this);
	}
	else if (rhs < 0) {
		/* a -(-b) == a + b */
		*this -= abs(rhs);
	}
	else if (*this < 0) {
		/* a < 0 && b >= 0 => -a -b == -(abs(a) + b)*/
		*this = -(abs(*this) + rhs);
	}
	else if (rhs > *this) {
		/* if a and b both >= 0 and b > a, calculate -(b - a) */
		*this = -(rhs - *this);
	}
	else {
		/* Both a and b >= 0 AND b is guaranteed to be >= a*/
		// Calculate new whole part
		assert(!subtractionExceedsLimits(_w, rhs._w));
		long long nw_w = _w - rhs._w;
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactors(_d, rhs._d);

		assert(!multiplicationExceedsLimits(_n, factor_left) 
		&& !multiplicationExceedsLimits(rhs._n, factor_right)
		&& !subtractionExceedsLimits((_n * factor_left), (rhs._n * factor_right)));
		long long nw_n = (_n * factor_left) - (rhs._n * factor_right);
		long long nw_d = lcm;
		if (nw_n < 0 && nw_w > 0) {
			/* If we end up with something like -3/7 we have to adjust the 
			whole part if it exists: we take one away from whole
			then add 1 - new fraction to it */
			assert(nw_n != LONG_LONG_MIN);
			nw_w -= 1;
			assert(!additionExceedsLimits(nw_d, nw_n));
			nw_n = nw_d + nw_n; // + because nw_n is < 0
		}
		_w = nw_w;
		_n = nw_n;
		_d = nw_d;
		simplify();
	}
	return *this;
}

Rational	&Rational::operator*=(const Rational &rhs) {
	if (*this == 0 || rhs == 0) {
		*this = 0;
	}
	else if (*this < 0 || rhs < 0) {
		/* If both terms < 0, discard the -1 */
		if (*this < 0 && rhs < 0) {
			*this = abs(*this) * abs(rhs);
		}
		else {
			*this = -(abs(*this) * abs(rhs));
		}
	}
	else {
		// Multiply lhs by whole part of rhs
		Rational 	lhs_times_rhs_w = *this * rhs._w;
		lhs_times_rhs_w.simplify();

		// Multiply whole part of lhs by fractional part of rhs
		assert(!multiplicationExceedsLimits(_w, rhs._n));
		long long 	nw_w = (_w * rhs._n) / rhs._d;
		
		assert(!multiplicationExceedsLimits(nw_w, rhs._d)
		&& !subtractionExceedsLimits((_w * rhs._n), (nw_w * rhs._d)));
		long long 	rest_n = (_w * rhs._n) - (nw_w * rhs._d);
		Rational lhs_w_times_rhs_fract = Rational(rest_n, rhs._d, nw_w);

		// Multiply fractional part of lhs by fractional part of rhs
		assert(!multiplicationExceedsLimits(_n, rhs._n)
		&& !multiplicationExceedsLimits(_d, rhs._d));
		Rational 	lhs_fract_times_rhs_fract = Rational(_n * rhs._n, _d * rhs._d);
		
		// Add all results together
		*this = lhs_times_rhs_w + lhs_w_times_rhs_fract + lhs_fract_times_rhs_fract;
	}
	return *this;
}

Rational	&Rational::operator/=(const Rational &rhs) {
	assert(rhs != 0);
	if (*this == 0) {
		*this = 0;
	}
	else if (*this < 0 || rhs < 0) {
		/* If both terms < 0, discard the -1 */
		if (*this < 0 && rhs < 0) {
			*this = abs(*this) / abs(rhs);
		}
		else {
			*this = -(abs(*this) / abs(rhs));
		}
	}
	else {
		// Both numbers are positive > 0
		Rational inverted_rhs = rhs.invert();

		// Divide whole part of lhs by rhs
		Rational w_res = _w * inverted_rhs;

		// Divide fractional lhs by rhs
		Rational fract_lhs = *this;
		fract_lhs._w = 0;

		Rational fract_res = fract_lhs * inverted_rhs;

		*this = w_res + fract_res;
	}
	return *this;
}

std::tuple<long long, long long, long long>	Rational::getDenomFactors(long long d_left, long long d_right) {
	/* LCM is always positive */
	long long lcm = std::lcm(d_left, d_right);
	long long factor_left = lcm / d_left;
	long long factor_right = lcm / d_right;

	return std::make_tuple(lcm, factor_left, factor_right); 
}

Rational		abs(const Rational &rhs) {
	assert(!(rhs._n == LONG_LONG_MIN || rhs._w == LONG_LONG_MIN));
	Rational tmp = rhs;
	tmp._n = llabs(tmp._n);
	tmp._w = llabs(tmp._w);
	return (tmp);
}

Rational	Rational::getGcd() const {
	if (_w == 0) {
		return (Rational(_n, _d));
	}
	else {
		long long n = std::gcd(_n, _w);
		long long d = std::lcm(_d, 1);
		return (Rational(n, d));
	}
}

Rational::operator long double() const {
	return ((long double)_n / (long double)_d);
}

Rational::operator long long() const {
	return ((long long)(_n / _d));
}

void		Rational::fixSigns() {
/* Fix signs if appropriate */
	if (_d < 0 && _n < 0) {
		// if both numerator and denominator are negative, factor out negative sign
		assert(_d != LONG_LONG_MIN && _n != LONG_LONG_MIN);
		_d = llabs(_d);
		_n = llabs(_n);
	}
	if (_d < 0 && _n >= 0) {
		// Move negative sign to numerator if appropriate
		assert(_d != LONG_LONG_MIN);
		_d = llabs(_d);
		_n *= -1;
	}
	if (_w < 0 && _n > 0) {
		// If whole part < 0, make numerator explicitely negative as well for parsing
		_n = -_n;
	}
}

void		Rational::simplify() {
	fixSigns();

	/* Get any whole parts from fraction */
	assert(_n != LONG_LONG_MIN);
	long long wholes  = _n / _d;

	factorGcd(_n, _d);
	/* Move leftover wholes from fraction to _w	*/
	if (wholes != 0) {
		if (_w < 0 && wholes > 0) {
			/* If wholes > 0, so is _n */
			_w -= wholes;
		}
		else {
			_w += wholes;
		}
		_n -= wholes * _d;
	}
	/* If _w is a positive number and _n is a negative number,
	subtract it from the whole part and adjust _n */
	if (_w > 0 && _n < 0) {
		_w -= 1;
		_n = _d + _n;
	}
	if (_n < 0 && _w != 0) {
		/* We like to keep the minus on the fractional part implicit once 
		Rational has been created */
		_n = llabs(_n);
	}
}

Rational		Rational::invert() const {
	Rational 	n = *this;
	long long 	nw_d;

	nw_d = n._n + (n._w * n._d);
	n._w = 0;
	n._n = n._d;
	n._d = nw_d;
	return n;
}

Rational		getGcd(const Rational &lhs, const Rational &rhs) {
	Rational lhs_gcd = lhs.getGcd();
	Rational rhs_gcd = rhs.getGcd();
	return Rational(std::gcd(lhs_gcd._n, rhs_gcd._n), std::lcm(lhs_gcd._d, rhs_gcd._d));
}

Rational		operator+(const Rational &lhs, const Rational &rhs) {
	Rational nw = lhs;
	nw += rhs;
	return nw;
}

Rational		operator-(const Rational &lhs, const Rational &rhs) {
	Rational nw = lhs;
	nw -= rhs;
	return nw;
}

Rational		operator*(const Rational &lhs, const Rational &rhs) {
	Rational nw = lhs;
	nw *= rhs;
	return nw;
}

Rational		operator/(const Rational &lhs, const Rational &rhs) {
	Rational nw = lhs;
	nw /= rhs;
	return nw;
}

std::ostream	&operator<<(std::ostream &os, const Rational &r) {
	// TO DO: get whole part etc
	if (r == 0) {
		os << 0;
	}
	else {
		if (r._w != 0)
			os << r._w;
		if (r._w != 0 && r._n != 0)
		 	os << "(";
		if (r._n != 0)
			os << r._n << "/" << r._d;
		if (r._w != 0 && r._n != 0)
			os << ")";
	}
	return os;
}
