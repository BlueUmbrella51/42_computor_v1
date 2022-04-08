#include "Root.h"
#include "math_helpers.h"


void		rationalize(Root &numer, const Root &denom) {
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	Root denomRoot = Root(denom._root);

	numer *= denomRoot;
	
	/* multiplying root by itself just gives you the number under the sqrt */
	numer._divisor = denom._whole * denom._root;
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
	std::cout << "simplify fraction\n";
	r.combineWholeNumerator();
	std::cout << "Combine fraction: " << r << "\n";
	Root numer = Root(r.getNum());
	std::cout << "Denom before root: " << r.getDenom() << "\n";
	Root denom = Root(r.getDenom());

	std::cout << "Numer: " << numer << " Denom: " << denom << "\n";
	rationalize(numer, denom);
	std::cout << "Numerator simplified: " << numer << "\n";
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
	long long 	nw_whole = getWhole() * rhs.getWhole();
	Root 		nw_root = Root(getRoot() * rhs.getRoot());
	
	nw_whole *= nw_root.getWhole();
	_whole = nw_whole;
	_root = nw_root.getRoot();
	std::cout << "New whole: " << nw_whole << " New root: " << nw_root << "\n";
	return *this;
}

Root		&Root::operator/=(const Root &rhs) {
	// TODO: COMPLEX
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	rationalize(*this, rhs);
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
	if (x._whole != 1 || x.getRoot() == 1) {
		os << x._whole;
	}
	if ((x.getRoot() != 1)) {
		os << "V" << x._root;
	}
	if (x._type == Root::Type::imaginary) {
		os << "i";
	}
	if (x._divisor != 1) {
		os << " / " << x._divisor;
	}
	return os;
}
