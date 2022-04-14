#include "SquareRoot.h"
#include "math_helpers.h"
#include <iomanip>

void		rationalize(SquareRoot &numer, const SquareRoot &denom) {
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	SquareRoot denomSquareRoot = SquareRoot(denom._root);

	numer *= denomSquareRoot;
	
	/* multiplying root by itself just gives you the number under the sqrt */
	numer._divisor = (Rational)denom._whole * (Rational)denom._root;
}

SquareRoot::SquareRoot(Rational n) : _root{1}, _whole{1}, _degree{2}, 
	_type{SquareRoot::Type::real}, _divisor{1} {
	if (n == 0) {
		std::cout << "Root cannot be zero, setting it to 1.\n";
		n = 1;
	}
	if (n < 0) {
		_type = Type::imaginary;
		n = abs(n);
	}
	auto val = n.getVal();
	if (_degree > 0) {
		if (n.isFraction()) {
			simplifyFraction(std::get<Fraction>(val));
		}
		else {
			simplifyNumerical(std::get<Numerical>(val));
		}
	}
}

void	SquareRoot::simplifyFraction(Fraction &r) {
	r.combineWholeNumerator();
	SquareRoot numer = SquareRoot(r.getNum());
	SquareRoot denom = SquareRoot(r.getDenom());

	rationalize(numer, denom);
	_root = numer._root;
	_whole = Fraction(numer._whole, numer._divisor);
}

void	SquareRoot::simplifyNumerical(Numerical &n) {
	std::visit([&](auto arg) {
		auto [w, r] = simplify_root(arg, _degree);
		_whole = w;
		_root = r;
	}, n.getVal());
}

SquareRoot	&SquareRoot::operator=(const SquareRoot &rhs) {
	if (this != &rhs) {
		_root = rhs.getSquareRoot();
		_whole = rhs.getWhole();
		_degree = rhs.getDegree();
		_type = rhs.getType();
		_divisor = rhs.getDivisor();
	}
	return *this;
}

Numerical	SquareRoot::getSquareRoot() const {
	return _root;
}

Rational	SquareRoot::getWhole() const {
	return _whole;
}

int			SquareRoot::getDegree() const {
	return _degree;
}

SquareRoot::Type	SquareRoot::getType() const {
	return _type;
}

Rational	SquareRoot::getDivisor() const {
	return _divisor;
}

void		SquareRoot::setType(Type t) {
	_type = t;
}

bool		sameTypeAndSquareRoot(const SquareRoot &lhs, const SquareRoot &rhs) {
	return (lhs.getType() == rhs.getType()
	&& rhs.getSquareRoot() == rhs.getSquareRoot());
}

SquareRoot		&SquareRoot::operator+=(const SquareRoot &rhs) {
	if (!sameTypeAndSquareRoot(*this, rhs)) {
		std::cout << "Cannot add roots of different types or roots, exiting now\n";
	}
	else {
		_whole += rhs.getWhole();
	}
	return *this;
}

SquareRoot::operator std::string() const {
	std::string res = "";

	if (_whole != 1) {
		res += (std::string)_whole;
	}
	if (_root != 1) {
		res += "√";
		res += (std::string)_root;
	}
	if (_type == Type::imaginary) {
		res += "𝑖";
	}
	return res;
}

SquareRoot::operator long double() const {
	if (_root == 1) {
		return (long double)_whole;
	}
	else {
		long double root = std::pow((long double)_root, 1.0/(long double)_degree);
		return (long double)_whole * root;
	}
}

bool		SquareRoot::hasRealNumericSolution() const {
	/* If root is of no influence or any component is 
	floating point, solution is numeric */
	return ((_root == 1 || _root.isFloating()) && _type == Type::real);
}

Rational	SquareRoot::getNumericalSolution() const {
	if (_root == 1) {
		return _whole;
	}
	else if (_root.isFloating()) {
		return std::pow((long double)_root, 1.0f / _degree);
	}
	else {
		// SquareRoot is integral
		long double res = _whole;

		res *= std::pow((long double)_root, 1.0 / _degree);
		return res;
	}
}

SquareRoot		&SquareRoot::operator-=(const SquareRoot &rhs) {
	if (!sameTypeAndSquareRoot(*this, rhs)) {
		std::cout << "Cannot add roots of different types or roots, exiting now\n";
	}
	else {
		_whole -= rhs.getWhole();
	}
	return *this;
}

SquareRoot		&SquareRoot::operator*=(const SquareRoot &rhs) {
	// TODO: complex and real?
	Rational 		nw_whole = getWhole() * rhs.getWhole();
	SquareRoot 		nw_root = SquareRoot(getSquareRoot() * rhs.getSquareRoot());

	nw_whole *= nw_root.getWhole();
	_whole = nw_whole;
	_root = nw_root.getSquareRoot();
	if (rhs._type == SquareRoot::Type::imaginary) {
		_type = SquareRoot::Type::imaginary;
	}
	return *this;
}

// SquareRoot		&SquareRoot::operator/=(const SquareRoot &rhs) {
// 	// TODO: COMPLEX
// 	/* Normalize the "fraction" (move it from denominator to nominator) 
// 	by multiplying numerator and denominator by root part of denominator */

// 	rationalize(*this, rhs);
// 	return *this;
// }

SquareRoot		&SquareRoot::operator/=(const Rational &rhs) {
	// TODO: COMPLEX
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	_whole /= rhs;
	return *this;
}

SquareRoot		operator*(const SquareRoot &lhs, const SquareRoot &rhs) {
	SquareRoot tmp = lhs;
	return (tmp *= rhs);
}

bool		operator==(const SquareRoot &lhs, const SquareRoot &rhs) {
	return (lhs.getSquareRoot() == rhs.getSquareRoot()
	&& lhs.getType() == rhs.getType()
	&& lhs.getWhole() == rhs.getWhole()
	&& lhs.getDegree() == rhs.getDegree());
}

bool		operator!=(const SquareRoot &lhs, const SquareRoot &rhs) {
	return !(lhs == rhs);
}

std::ostream    		&operator<<(std::ostream &os, const SquareRoot &x) {
	os << (std::string)x;
	return os;
}

bool		SquareRoot::isFloating() const {
	return (_root.isFloating() || _whole.isFloating()
	|| _divisor.isFloating());
}

SquareRoot		operator/(const SquareRoot &lhs, const Rational &rhs) {
	SquareRoot n = lhs;

	n._whole /= rhs;
	return n;
}
