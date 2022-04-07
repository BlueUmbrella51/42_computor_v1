#include "Root.h"

/* Root class */
void	Root::simplify() {
	/* Any square sqrt(n) can be represented as sqrt(f1) * sqrt(f2).
	We are looking for the largest perfect square f1 */
	std::visit([=](auto root) {
		auto res = simplify_root(root, _degree);
		_whole = std::get<0>(res);
		_root = std::get<1>(res);
	}, (getRoot().getVal()));
}

Root::Root(Numerical n, int degree) : _root{n}, _whole{1}, _degree{degree}, 
	_type{Root::Type::real}, _divisor{1} {
	if (_root < 0) {
		_type = Type::imaginary;
		_root = abs(_root);
	}
	simplify();
}

Root	&Root::operator=(const Root &rhs) {
	if (*this != rhs) {
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

long long	Root::getWhole() const {
	return _whole;
}

int			Root::getDegree() const {
	return _degree;
}

Root::Type	Root::getType() const {
	return _type;
}

Numerical	Root::getDivisor() const {
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
	// TODO: complex and real. ONLY WORKS FOR SECOND DEGREE??
	/* Normalize the "fraction" (move it from denominator to nominator) 
	by multiplying numerator and denominator by root part of denominator */
	Root denomRoot = Root(rhs.getRoot());
	std::cout << "Root part of divisor: " << denomRoot << "\n";
	*this *= denomRoot;
	std::cout << "New numerator: " << *this << "\n";

	/* multiplying root by itself just gives you the number under the sqrt */
	_divisor = rhs.getWhole() * rhs.getRoot();
	std::cout << "New divisor: " << _divisor << "\n";

	long long gcd = (long long)getGcd(_whole, _divisor);
	std::cout << "Gcd: " << gcd << "\n";
	_whole /= gcd;
	_divisor /= gcd;
	std::cout << "Result: " << *this << "\n";
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
	if (abs(x._whole) != 1) {
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
