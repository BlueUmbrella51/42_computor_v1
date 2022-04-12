#include "Root.h"
#include "math_helpers.h"


void		rationalize(Root &numer, const Root &denom) {
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	Root denomRoot = Root(denom._root);

	numer *= denomRoot;
	
	/* multiplying root by itself just gives you the number under the sqrt */
	numer._divisor = (Rational)denom._whole * (Rational)denom._root;
}

Root::Root(Rational n, int degree) : _root{0}, _whole{1}, _degree{degree}, 
	_type{Root::Type::real}, _divisor{1} {
	if (n < 0) {
		_type = Type::imaginary;
		n = abs(n);
	}
	auto val = n.getVal();
	if (n.isFraction()) {
		simplifyFraction(std::get<Fraction>(val));
	}
	else {
		simplifyNumerical(std::get<Numerical>(val));
	}
}

void	Root::simplifyFraction(Fraction &r) {
	r.combineWholeNumerator();
	Root numer = Root(r.getNum());
	Root denom = Root(r.getDenom());

	rationalize(numer, denom);
	_root = numer._root;
	_whole = Fraction(numer._whole, numer._divisor);
}

void	Root::simplifyNumerical(Numerical &n) {
	std::visit([&](auto arg) {
		auto [w, r] = simplify_root(arg, _degree);
		_whole = w;
		_root = r;
	}, n.getVal());
}

Root	&Root::operator=(const Root &rhs) {
	if (this != &rhs) {
		_root = rhs.getRoot();
		_whole = rhs.getWhole();
		_degree = rhs.getDegree();
		_type = rhs.getType();
		_divisor = rhs.getDivisor();
	}
	return *this;
}

Numerical	Root::getRoot() const {
	return _root;
}

Rational	Root::getWhole() const {
	return _whole;
}

int			Root::getDegree() const {
	return _degree;
}

Root::Type	Root::getType() const {
	return _type;
}

Rational	Root::getDivisor() const {
	return _divisor;
}

void		Root::setType(Type t) {
	_type = t;
}

bool		sameTypeAndRoot(const Root &lhs, const Root &rhs) {
	return (lhs.getType() == rhs.getType()
	&& rhs.getRoot() == rhs.getRoot());
}

Root		&Root::operator+=(const Root &rhs) {
	if (!sameTypeAndRoot(*this, rhs)) {
		std::cout << "Cannot add roots of different types or roots, exiting now\n";
	}
	else {
		_whole += rhs.getWhole();
	}
	return *this;
}

Root::operator std::string() const {
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

Root::operator long double() const {
	if (_root == 1) {
		return (long double)_whole;
	}
	else {
		auto root = std::pow((long double)_root, 1.0f/(long double)_degree);
		return (long double)_whole * root;
	}
}

bool		Root::hasNumericSolution() const {
	/* If root is of no influence or any component is 
	floating point, solution is numeric */
	return (_root == 1 || _root.isFloating());
}

Rational	Root::getNumericalSolution() const {
	if (_root == 1) {
		return _whole;
	}
	else if (_root.isFloating()) {
		return std::pow((long double)_root, 1.0f / _degree);
	}
	else {
		// Root is integral
		long double res = _whole;

		res *= std::pow((long double)_root, 1.0 / _degree);
		return res;
	}
}

Root		&Root::operator-=(const Root &rhs) {
	if (!sameTypeAndRoot(*this, rhs)) {
		std::cout << "Cannot add roots of different types or roots, exiting now\n";
	}
	else {
		_whole -= rhs.getWhole();
	}
	return *this;
}

Root		&Root::operator*=(const Root &rhs) {
	// TODO: complex and real?
	Rational 	nw_whole = getWhole() * rhs.getWhole();
	Root 		nw_root = Root(getRoot() * rhs.getRoot());
	
	nw_whole *= nw_root.getWhole();
	_whole = nw_whole;
	_root = nw_root.getRoot();
	return *this;
}

Root		&Root::operator/=(const Root &rhs) {
	// TODO: COMPLEX
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	rationalize(*this, rhs);
	return *this;
}

Root		&Root::operator/=(const Rational &rhs) {
	// TODO: COMPLEX
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	_whole /= rhs;
	return *this;
}

Root		operator*(const Root &lhs, const Root &rhs) {
	Root tmp = lhs;
	return (tmp *= rhs);
}

bool		operator==(const Root &lhs, const Root &rhs) {
	return (lhs.getRoot() == rhs.getRoot()
	&& lhs.getType() == rhs.getType()
	&& lhs.getWhole() == rhs.getWhole()
	&& lhs.getDegree() == rhs.getDegree());
}

bool		operator!=(const Root &lhs, const Root &rhs) {
	return !(lhs == rhs);
}

std::ostream    		&operator<<(std::ostream &os, const Root &x) {
	os << (std::string)x;
	return os;
}

bool		Root::isFloating() const {
	return (_root.isFloating() || _whole.isFloating()
	|| _divisor.isFloating());
}

Root		operator/(const Root &lhs, const Rational &rhs) {
	Root n = lhs;

	n._whole /= rhs;
	return n;
}
