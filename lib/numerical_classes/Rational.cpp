#include "Rational.h"
#include <numeric>
#include <iostream>
#include <tuple>
#include <assert.h>
#include <limits.h>

Rational::Rational():
_w{0}, _n{0}, _d{1} {

}

Rational::Rational(long long whole):
_w{whole}, _n{0}, _d{1} {

}

Rational::Rational(long long n, long long d):
 _w{0}, _n{n}, _d{d} {
	if (d == 0) {
		std::cout << "Warning: denominator can't be 0, setting rational to 0.\n";
		_n = 0;
		_d = 1;
	}
	else
		simplify();
}

Rational::Rational(long long w, long long n, long long d) :
_w{w}, _n{n}, _d{d} {
	if (d == 0) {
		std::cout << "Warning: denominator can't be 0, setting rational to 0.\n";
		_w = 0;
		_n = 0;
		_d = 1;
	}
	else
		simplify();
}

Rational::Rational(const Rational &rhs) :
_w{rhs._w}, _n{ rhs._n }, _d{rhs._d} {

}

long long	Rational::getWhole() const {
	return _w;
}

long long	Rational::getNum() const {
	return _n;
}

long long	Rational::getDenom() const {
	return _d;
}

std::tuple<long long, long long, long long> Rational::getValue() {
	return std::make_tuple(getWhole(), getNum(), getDenom());
}

Rational 	Rational::operator-() const {
	// TODO: copy?
	// If relevant part is long long min, we can't make it positive
	Rational tmp = *this;
	if (tmp._w != 0) {
		if (tmp._w == LLONG_MIN) {
			throw std::overflow_error("Cannot make minimum value of long long positive without causing overflow.\n");
		}
		tmp._w *= -1;
	}
	else {
		if (tmp._w == LLONG_MIN) {
			throw std::overflow_error("Cannot make minimum value of long long positive without causing overflow.\n");
		}
		tmp._n *= -1;
	}
	return tmp;
}

Rational	&Rational::operator=(const Rational &rhs) {
	if (this != &rhs) {
		this->_n = rhs._n;
		this->_d = rhs._d;
		this->_w = rhs._w;
	}
	return *this;
}

bool	operator==(const Rational &lhs, const Rational &rhs) {
	return (lhs.getWhole() == rhs.getWhole() && 
	(lhs.getNum() * rhs.getDenom()) == (rhs.getNum() * lhs.getDenom()));
}

// bool		Rational::operator==(const Rational &rhs) const {
// 	/* Returns true for equivalence, so 1(1/2) == 1(3/6) returns true */
// 	return (_w == rhs._w && (_n * rhs._d) == (rhs._n * _d));
// }

bool	operator!=(const Rational &lhs, const Rational &rhs) {
	return !(lhs == rhs);
}

bool		operator>(const Rational &lhs, const Rational &rhs) {
	if (lhs.getWhole() > rhs.getWhole()) { return true; }
	if (lhs.getWhole() < rhs.getWhole()) { return false; }
	auto [factor_left, factor_right] = getDenomFactors(lhs.getDenom(), rhs.getDenom());
	return (lhs.getNum() * factor_left > rhs.getNum() * factor_right);
}

bool		operator>=(const Rational &lhs, const Rational &rhs) {
	return (lhs > rhs || lhs == rhs);
}

bool		operator<(const Rational &lhs, const Rational &rhs) {
	if (lhs.getWhole() < rhs.getWhole()) { return true; }
	if (lhs.getWhole() > rhs.getWhole()) { return false; }
	auto [factor_left, factor_right] = getDenomFactors(lhs.getDenom(), rhs.getDenom());
	return (lhs.getNum() * factor_left < rhs.getNum() * factor_right);
}

bool		operator<=(const Rational &lhs, const Rational &rhs) {
	return (lhs < rhs || lhs == rhs);
}

// bool		Rational::operator>(const Rational &rhs) const {
// 	if (_w > rhs._w) { return true; }
// 	if (_w < rhs._w) {return false; }
// 	return ((_n * rhs._d) > (rhs._n * _d));
// }

// bool		Rational::operator>=(const Rational &rhs) const {
// 	return (*this > rhs || *this == rhs);
// }

// bool		Rational::operator<(const Rational &rhs) const {
// 	if (_w < rhs._w) { return true; }
// 	else { return ((_n * rhs._d) < (rhs._n * _d)); }
// }

// bool		Rational::operator<=(const Rational &rhs) const {
// 	return (*this < rhs || *this == rhs);
// }

Rational	&Rational::operator+=(const Rational &rhs){
	// a += b
	if (*this == 0) {
		*this = rhs;
	}
	else if (*this < 0 && rhs >= 0) {
		/* 	If a < 0 and b >= 0: -a + b == b - abs(a) */
		*this = rhs - abs(*this);
	}
	else if (rhs < 0) {
		/* a + - b == a - abs(b)*/
		*this -= abs(rhs);
	}
	else {
		/* Both a and b >= 0 */
		// Calculate new whole part
		/* Prevent overflow */
		if(additionExceedsLimits(_w, rhs._w)) {
			throw std::overflow_error("Cannot perform addition without causing overflow.\n");
		}
		long long nw_w = _w + rhs._w;
		
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactorsLcm(_d, rhs._d);

		/* Prevent multiplication overflow (factors and numerators are guaranteed to be positive) */
		if (multiplicationExceedsLimits(_n, factor_left)
		|| multiplicationExceedsLimits(rhs._n, factor_right)
		|| additionExceedsLimits((_n * factor_left), (rhs._n * factor_right))) {
			throw std::overflow_error("Cannot perform addition without causing overflow.\n");
		}
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
		*this = -rhs;
	}
	else if (rhs < 0) {
		/* a -(-b) == a + -b */
		*this += abs(rhs);
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
		if (subtractionExceedsLimits(_w, rhs._w)) {
			throw std::overflow_error("Cannot perform subtraction without causing overflow.\n");
		}
		long long nw_w = _w - rhs._w;
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactorsLcm(_d, rhs._d);

		if(multiplicationExceedsLimits(_n, factor_left) 
		|| multiplicationExceedsLimits(rhs._n, factor_right)
		|| subtractionExceedsLimits((_n * factor_left), (rhs._n * factor_right))) {
			throw std::overflow_error("Cannot perform subtraction without causing overflow.\n");
		}
		long long nw_n = (_n * factor_left) - (rhs._n * factor_right);
		long long nw_d = lcm;
		if (nw_n < 0 && nw_w > 0) {
			/* If we end up with something like -3/7 we have to adjust the 
			whole part if it exists: we take one away from whole
			then add 1 - new fraction to it */
			if (nw_n == LONG_LONG_MIN) {
				throw std::overflow_error("Cannot perform subtraction without causing overflow.\n");
			}
			nw_w -= 1;
			if (additionExceedsLimits(nw_d, nw_n)) {
				throw std::overflow_error("Cannot perform subtraction without causing overflow.\n");
			}
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
		// Rational 	lhs_times_rhs_w = *this * rhs._w;
		if (multiplicationExceedsLimits(rhs._w, _w) || multiplicationExceedsLimits(rhs._w, _n)) {
			throw std::overflow_error("Cannot perform multiplication without causing overflow.\n");
		}
		Rational lhs_times_rhs_w = Rational(_w * rhs._w, _n * rhs._w, _d);
		lhs_times_rhs_w.simplify();

		// Multiply whole part of lhs by fractional part of rhs
		if (multiplicationExceedsLimits(_w, rhs._n)) {
			throw std::overflow_error("Cannot perform multiplication without causing overflow.\n");
		}
		long long 	nw_w = (_w * rhs._n) / rhs._d;
		
		if (multiplicationExceedsLimits(nw_w, rhs._d)
		|| subtractionExceedsLimits((_w * rhs._n), (nw_w * rhs._d))) {
			throw std::overflow_error("Cannot perform multiplication without causing overflow.\n");
		}
		long long 	rest_n = (_w * rhs._n) - (nw_w * rhs._d);
		Rational lhs_w_times_rhs_fract = Rational(nw_w, rest_n, rhs._d);

		// Multiply fractional part of lhs by fractional part of rhs
		if (multiplicationExceedsLimits(_n, rhs._n)
		|| multiplicationExceedsLimits(_d, rhs._d)) {
			throw std::overflow_error("Cannot perform multiplication without causing overflow.\n");
		}
		Rational 	lhs_fract_times_rhs_fract = Rational(_n * rhs._n, _d * rhs._d);
		
		// Add all results together
		*this = lhs_times_rhs_w + lhs_w_times_rhs_fract + lhs_fract_times_rhs_fract;
	}
	return *this;
}

Rational	&Rational::operator/=(const Rational &rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Cannot divide by 0.\n");
	}
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

std::tuple<long long, long long, long long>	getDenomFactorsLcm(long long d_left, long long d_right) {
	/* LCM is always positive */
	long long lcm = std::lcm(d_left, d_right);
	long long factor_left = lcm / d_left;
	long long factor_right = lcm / d_right;

	return std::make_tuple(lcm, factor_left, factor_right); 
}

std::tuple<long long, long long>		getDenomFactors(long long d_left, long long d_right) {
	long long lcm = std::lcm(d_left, d_right);
	long long factor_left = lcm / d_left;
	long long factor_right = lcm / d_right;

	return std::make_tuple(factor_left, factor_right);
}



Rational		abs(const Rational &rhs) {
	if (rhs._n == LONG_LONG_MIN || rhs._w == LONG_LONG_MIN) {
		throw std::overflow_error("Cannot take absolute value of minimum value of long long without causing overflow\n");
	}
	Rational tmp = rhs;
	tmp._n = llabs(tmp._n);
	tmp._w = llabs(tmp._w);
	return (tmp);
}

Rational	Rational::getGcd() const {
	if (_w == 0) {
		return (Rational(_n, _d));
	}
	else if (_n == 0) {
		return (Rational(_w));
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

Rational::operator std::string() const {
	std::string res = "";
	if (_w == 0 && _n == 0) {
		res += "0";
	}
	if (_w != 0) {
		res += std::to_string(_w);
		if (_n != 0) {
			res += "(";
		}
	}
	if (_n != 0) {
		res += std::to_string(_n) + "/" + std::to_string(_d);
		if (_w != 0) { res += ")"; }
	}
	return res;
}

void		Rational::fixSigns() {
/* Fix signs if appropriate */
	if (_d < 0 && _n < 0) {
		// if both numerator and denominator are negative, factor out negative sign
		if (_d == LONG_LONG_MIN || _n == LONG_LONG_MIN) {
			throw std::overflow_error("Cannot make minimum value of long long positive without causing overflow.\n");
		}
		_d = llabs(_d);
		_n = llabs(_n);
	}
	if (_d < 0 && _n >= 0) {
		// Move negative sign to numerator if appropriate
		if (_d == LONG_LONG_MIN) {
			throw std::overflow_error("Cannot make minimum value of long long positive without causing overflow.\n");
		}
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
	if (_n == LONG_LONG_MIN && _d == -1) {
		throw std::overflow_error("Cannot make minimum value of long long positive without causing overflow.\n");
	}
	long long wholes  = _n / _d;

	factorGcd(_n, _d);
	/* Move leftover wholes from fraction to _w	*/
	if (wholes != 0) {
		if (_w < 0 && wholes > 0) {
			/* If wholes > 0, so is _n */
			if (subtractionExceedsLimits(_w, wholes)) {
				throw std::overflow_error("Cannot perform subtraction without causing overflow.\n");
			}
			_w -= wholes;
		}
		else {
			if (additionExceedsLimits(_w, wholes)) {
				throw std::overflow_error("Cannot perform addition without causing overflow.\n");
			}
			_w += wholes;
		}
		if (multiplicationExceedsLimits(_d, wholes)
		|| subtractionExceedsLimits(_n, wholes * _d)) {
			throw std::overflow_error("Cannot perform addition without causing overflow.\n");
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
		if (_n == LONG_LONG_MIN) {
			throw std::overflow_error("Cannot convert long long min value to positive without causing overflow.\n");
		}
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
	/* The behaviour when w or n is 0, behaviour is slightly different: 
	instead of returning the higher bound, we return 1.
	*/
	if (lhs._n == 0 && rhs._n == 0) {
		return (Rational(std::gcd(lhs._w == 0 ? 1 : lhs._w, rhs._w == 0 ? 1 : rhs._w)));
	}
	else {
		Rational lhs_gcd = lhs.getGcd();
		Rational rhs_gcd = rhs.getGcd();

		if (lhs_gcd._n == 0) {
			lhs_gcd._n = 1;
		}
		if (rhs_gcd._n == 0) {
			rhs_gcd._n = 0;
		}
		return Rational(std::gcd(lhs._n == 0 ? 1 : lhs._n, rhs._n == 0 ? 1 : rhs._n), std::lcm(lhs_gcd._d, rhs_gcd._d));
	}
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
	try {
		Rational nw = lhs;
		nw /= rhs;
		return nw;
	}
	catch (std::overflow_error &e) {throw e;}
	catch (std::invalid_argument &e) {throw e;}
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
