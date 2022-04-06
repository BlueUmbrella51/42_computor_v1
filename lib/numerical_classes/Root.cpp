#include "Root.h"

/* root type */

// numerical		abs(numerical &r) {
// 	return std::visit([](auto &arg) {
// 			return (numerical(std::abs(arg)));
// 	}, r);
// }


// bool		operator==(const numerical &lhs, const numerical &rhs) {
// 	return std::visit([](auto &lhs, auto &rhs) {
// 		return (lhs == rhs);
// 	}, lhs, rhs);
// }

// bool		operator!=(const numerical &lhs, const numerical &rhs) {
// 	return !(lhs == rhs);
// }

// bool		operator<(const numerical &lhs, const numerical &rhs) {
// 	return std::visit([](auto &lhs, auto &rhs) {
// 		return (lhs < rhs);
// 	}, lhs, rhs);
// }

// std::ostream    		&operator<<(std::ostream &os, const numerical &x) {
// 	std::visit([&os](auto arg) {
// 		os << arg;
// 	}, x);
// 	return os;
// }

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
	// TODO: complex and real
	// auto nw_whole = getWhole() * rhs.getWhole();
	// auto nw_root = getRoot() * rhs.getRoot();
	// // Root nw_root = std::visit([](auto n1, auto n2) {
	// // 	return Root((n1 * n2));
	// // }, getRoot(), rhs.getRoot());
	// nw_whole *= nw_root.getWhole();
	// _whole = nw_whole;
	// _root = nw_root.getRoot();
	// std::cout << "New whole: " << nw_whole << " New root: " << nw_root << "\n";
	return *this;
}

Root		&Root::operator/=(const Root &rhs) {
	// TODO: complex and real
	/* Normalize the "fraction" */
	// Root denomRoot = Root(rhs.getRoot());
	// std::cout << "Root part of divisor: " << denomRoot << "\n";
	// *this *= denomRoot;
	// Numerical divisor = rhs.getRoot() * rhs.getWhole();
	// Numerical gcd = getGcd(_whole, divisor);
	// std::cout << "Divisor: " << divisor << "\n";
	// divisor = divisor / gcd;
	// _whole = _whole / (long long)gcd;
	// std::cout << *this;
	return *this;
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
	return os;
}
