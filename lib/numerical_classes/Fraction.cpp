#include "Fraction.h"
#include <numeric>
#include <iostream>
#include <tuple>
#include <limits.h>

Fraction::Fraction():
_w{0}, _n{0}, _d{1} {

}

Fraction::Fraction(long long whole):
_w{whole}, _n{0}, _d{1} {

}

Fraction::Fraction(long long n, long long d):
 _w{0}, _n{n}, _d{d} {
	if (d == 0) {
		std::cerr << "Warning: denominator can't be 0, setting rational to 0.\n";
		_n = 0;
		_d = 1;
	}
	else
		simplify();
}

Fraction::Fraction(long long w, long long n, long long d) :
_w{w}, _n{n}, _d{d} {
	if (d == 0) {
		std::cerr << "Warning: denominator can't be 0, setting rational to 0.\n";
		_w = 0;
		_n = 0;
		_d = 1;
	}
	else
		simplify();
}

Fraction::Fraction(const Fraction &rhs) :
_w{rhs._w}, _n{rhs._n}, _d{rhs._d} {
}

long long	Fraction::getWhole() const {
	return _w;
}

long long	Fraction::getNum() const {
	return _n;
}

long long	Fraction::getDenom() const {
	return _d;
}

std::tuple<long long, long long, long long> Fraction::getValue() {
	return std::make_tuple(getWhole(), getNum(), getDenom());
}

void		Fraction::setNumerator(long long n) {
	_n = n;
}

void		Fraction::setDenominator(long long d) {
	_d = d;
}

Fraction 	Fraction::operator-() const {
	Fraction tmp = *this;
	if (tmp._w != 0) {
		tmp._w = safeMultiplication(tmp._w, -1);
	}
	else {
		tmp._n = safeMultiplication(tmp._n, -1);
	}
	return tmp;
}

Fraction	&Fraction::operator=(const Fraction &rhs) {
	if (this != &rhs) {
		this->_n = rhs._n;
		this->_d = rhs._d;
		this->_w = rhs._w;
	}
	return *this;
}

bool	operator==(const Fraction &lhs, const Fraction &rhs) {
	return (lhs.getWhole() == rhs.getWhole() && 
	(lhs.getNum() * rhs.getDenom()) == (rhs.getNum() * lhs.getDenom()));
}

bool	operator!=(const Fraction &lhs, const Fraction &rhs) {
	return !(lhs == rhs);
}

bool		operator>(const Fraction &lhs, const Fraction &rhs) {
	if (lhs.getWhole() > rhs.getWhole()) { return true; }
	if (lhs.getWhole() < rhs.getWhole()) { return false; }
	auto [factor_left, factor_right] = getDenomFactors(lhs.getDenom(), rhs.getDenom());
	return ((lhs.getNum() * factor_left) > (rhs.getNum() * factor_right));
}

bool		operator>=(const Fraction &lhs, const Fraction &rhs) {
	return (lhs > rhs || lhs == rhs);
}

bool		operator<(const Fraction &lhs, const Fraction &rhs) {
	return !(lhs >= rhs);
}

bool		operator<=(const Fraction &lhs, const Fraction &rhs) {
	return (lhs < rhs || lhs == rhs);
}

Fraction	&Fraction::operator+=(const Fraction &rhs){
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
		long long nw_w = safeAddition(_w, rhs._w);//_w + rhs._w;
		
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactorsLcm(_d, rhs._d);

		long long nw_n = safeAddition(safeMultiplication(_n, factor_left), safeMultiplication(rhs._n, factor_right));
		long long nw_d = lcm;

		_w = nw_w;
		_n = nw_n;
		_d = nw_d;
		simplify();
	}
	return *this;
}

Fraction	&Fraction::operator-=(const Fraction &rhs) {
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
		long long nw_w = safeSubtraction(_w, rhs._w);//_w - rhs._w;
		// Calculate new fraction
		auto [lcm, factor_left, factor_right] = getDenomFactorsLcm(_d, rhs._d);

		long long nw_n = safeSubtraction(safeMultiplication(_n, factor_left), safeMultiplication(rhs._n, factor_right));
		long long nw_d = lcm;
		if (nw_n < 0 && nw_w > 0) {
			/* If we end up with something like -3/7 we have to adjust the 
			whole part if it exists: we take one away from whole
			then add 1 - new fraction to it */
			nw_w = safeSubtraction(nw_w, 1);
			nw_n = safeAddition(nw_d, nw_n); // + because nw_n is < 0
		}
		_w = nw_w;
		_n = nw_n;
		_d = nw_d;
		simplify();
	}
	return *this;
}

Fraction	&Fraction::operator*=(const Fraction &rhs) {
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
		Fraction 	lhs_times_rhs_w = Fraction(safeMultiplication(_w, rhs._w), safeMultiplication(_n, rhs._w), _d);

		// Multiply whole part of lhs by fractional part of rhs
		long long 	nw_w = safeMultiplication(_w, rhs._n)/ rhs._d;
		
		long long 	rest_n = safeSubtraction(safeMultiplication(_w, rhs._n), safeMultiplication(nw_w, rhs._d));
		Fraction 	lhs_w_times_rhs_fract = Fraction(nw_w, rest_n, rhs._d);

		// Multiply fractional part of lhs by fractional part of rhs
		Fraction 	lhs_fract_times_rhs_fract = Fraction(safeMultiplication(_n, rhs._n), safeMultiplication(_d, rhs._d));
		
		// Add all results together
		*this = lhs_times_rhs_w + lhs_w_times_rhs_fract + lhs_fract_times_rhs_fract;
	}
	return *this;
}

Fraction	&Fraction::operator/=(const Fraction &rhs) {
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
		Fraction inverted_rhs = rhs.invert();

		// Divide whole part of lhs by rhs
		Fraction w_res = _w * inverted_rhs;

		// Divide fractional lhs by rhs
		Fraction fract_lhs = *this;
		fract_lhs._w = 0;

		Fraction fract_res = fract_lhs * inverted_rhs;

		*this = w_res + fract_res;
	}
	return *this;
}

std::tuple<long long, long long, long long>	getDenomFactorsLcm(long long d_left, long long d_right) {
	/* LCM is always positive */
	long long lcm = std::lcm(d_left, d_right);
	long long factor_left = safeDivision(lcm, d_left);
	long long factor_right = safeDivision(lcm, d_right);

	return std::make_tuple(lcm, factor_left, factor_right); 
}

std::tuple<long long, long long>		getDenomFactors(long long d_left, long long d_right) {
	long long lcm = std::lcm(d_left, d_right);
	long long factor_left = safeDivision(lcm, d_left);
	long long factor_right = safeDivision(lcm, d_right);

	return std::make_tuple(factor_left, factor_right);
}

void			Fraction::combineWholeNumerator() {
	int sign = _w < 0 ? -1 : 1;

	_n = safeAddition(_n, safeMultiplication(safeAbs(_w), _d));
	_n = safeMultiplication(_n, sign);
	_w = 0;
}

Fraction		abs(const Fraction &rhs) {
	Fraction tmp = rhs;
	tmp._n = safeAbs(tmp._n);
	tmp._w = safeAbs(tmp._w);
	return (tmp);
}

Fraction	Fraction::getGcd() const {
	if (_w == 0) {
		return (Fraction(_n, _d));
	}
	else if (_n == 0) {
		return (Fraction(_w));
	}
	else {
		/* n, w and d cannot be zero in this case*/
		long long n = std::gcd(_n, _w);
		long long d = std::lcm(_d, 1);
		return (Fraction(n, d));
	}
}

Fraction::operator long double() const {
	long long w = _w;
	long long n = _n;
	long long d = _d;
	
	if (_w < 0) {
		n = -n;
	}
	long double res = ((long double)n / (long double)d);
	return (long double)w + res;
}

Fraction::operator long long() const {
	return ((long long)safeDivision(_n, _d));
}

Fraction::operator std::string() const {
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
		res += std::to_string(_n);
		if (_d != 1) {
			res += "/" + std::to_string(_d);
		}
		if (_w != 0) { res += ")"; }
	}
	return res;
}

void		Fraction::fixSigns() {
/* Fix signs if appropriate */
	if (_d < 0 && _n < 0) {
		_d = safeAbs(_d);
		_n = safeAbs(_n);
	}
	if (_d < 0 && _n >= 0) {
		// Move negative sign to numerator if appropriate
		if (_d == LLONG_MIN) {
			throw std::overflow_error("Cannot make minimum value of long long positive without causing over- or underflow.\n");
		}
		_d = safeAbs(_d);
		_n *= -1;
	}
	if (_w < 0 && _n > 0) {
		// If whole part < 0, make numerator explicitely negative as well for parsing
		_n = -_n;
	}
}

void		Fraction::simplify() {
	fixSigns();

	/* Get any whole parts from fraction */
	long long wholes  = safeDivision(_n, _d);

	factorGcd(_n, _d);
	/* Move leftover wholes from fraction to _w	*/
	if (wholes != 0) {
		if (_w < 0 && wholes > 0) {
			/* If wholes > 0, so is _n */
			_w -= wholes; // Can't overflow because different signs
		}
		else {
			_w = safeAddition(_w, wholes);
		}
		_n = safeSubtraction(_n, safeMultiplication(wholes, _d));
	}
	/* If _w is a positive number and _n is a negative number,
	subtract it from the whole part and adjust _n */
	if (_w > 0 && _n < 0) {
		_w -= 1;
		_n = safeAddition(_d, _n);
	}
	if (_n < 0 && _w != 0) {
		/* We like to keep the minus on the fractional part implicit once 
		Fraction has been created */
		_n = safeAbs(_n);
	}
}

Fraction		Fraction::invert() const {
	Fraction 	n = *this;
	long long 	nw_d;

	nw_d = safeAddition(n._n, safeMultiplication(n._w, n._d));
	n._w = 0;
	n._n = n._d;
	n._d = nw_d;
	return n;
}

Fraction		getGcd(const Fraction &lhs, const Fraction &rhs) {
	/* The behaviour when w or n is 0, behaviour is slightly different: 
	instead of returning the higher bound, we return 1.
	*/
	if (lhs._n == 0 && rhs._n == 0) {
		return (Fraction(std::gcd(lhs._w == 0 ? 1 : lhs._w, rhs._w == 0 ? 1 : rhs._w)));
	}
	else {
		Fraction lhs_gcd = lhs.getGcd();
		Fraction rhs_gcd = rhs.getGcd();

		if (lhs_gcd._n == 0) {
			lhs_gcd._n = 1;
		}
		if (rhs_gcd._n == 0) {
			rhs_gcd._n = 0;
		}
		return Fraction(std::gcd(lhs._n == 0 ? 1 : lhs._n, rhs._n == 0 ? 1 : rhs._n), std::lcm(lhs_gcd._d, rhs_gcd._d));
	}
}

Fraction		operator+(const Fraction &lhs, const Fraction &rhs) {
	Fraction nw = lhs;
	nw += rhs;
	return nw;
}

Fraction		operator-(const Fraction &lhs, const Fraction &rhs) {
	Fraction nw = lhs;
	nw -= rhs;
	return nw;
}

Fraction		operator*(const Fraction &lhs, const Fraction &rhs) {
	Fraction nw = lhs;
	nw *= rhs;
	return nw;
}

Fraction		operator/(const Fraction &lhs, const Fraction &rhs) {
	Fraction nw = lhs;
	nw /= rhs;
	return nw;
}

std::ostream	&operator<<(std::ostream &os, const Fraction &r) {
	os << (std::string)r;
	return os;
}
