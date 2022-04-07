#include "Radical.h"

Radical::Radical(Rational discriminant, int degree) :
_degree{degree} {
	std::cout << "Discriminant: " << discriminant << "\n";
	auto [whole, radical] = simplifyRadical(abs(discriminant), _degree);
	_whole = whole;
	_radical = radical;
	std::cout << "Whole: " << _whole << " Radicant: " << _radical << "\n";
	if (_radical.isFraction()) { _radicalType = arithmeticType::fraction; }
	else if (_radical.isFloating()) { _radicalType = arithmeticType::floating; }
	else { _radicalType = arithmeticType::integral; }
	if (discriminant < 0) { _type = Type::imaginary; }
	else { _type = Type::real; }
	_solution = getSolution();
}

bool	Radical::hasSignificantRadicant() const {
	return (_radical != 1);
}

bool 	Radical::hasFloatingPointRadicant() const {
	return (_radicalType == arithmeticType::floating);
}

std::optional<Rational>		Radical::getSolution() {
	if (hasFloatingPointRadicant()) {
		return std::pow(_radical.toFloating(), (long double)1/(long double)_degree);
	}
	else if (!hasSignificantRadicant()) {
		return _whole;
	}
	else { return std::nullopt; }
}

std::ostream		&operator<<(std::ostream &os, const Radical &x) {
	if (x._solution) {
		os << "Solution: " << x._solution.value() << "\n";
	}
	else {
		if (abs(x._whole) > 1) {
			os << "Whole: " << x._whole << "\n";
		}
		if (x.hasSignificantRadicant()) {
			os << "Radicant: " << "V" << x._radical << "\n";
		}
	}
	return os;
}
