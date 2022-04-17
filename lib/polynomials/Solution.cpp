#include "Solution.h"

CompoundSolution::CompoundSolution(char sign, Rational l, SquareRoot r) :
_sign{sign}, _isImaginary{r.getType() == SquareRoot::Type::imaginary},
_commonFactor{1}, _cfIsImag{false}, _left{l}, 
_leftIsImag{false}, _right{r}, _rev{false} {
	if (_left != 0) {
		factor();
		adjustOrder();
	}
}

void	CompoundSolution::factor() {
	/* Factor out any common factors */
	_commonFactor = getGcd(_left, _right.getWhole());
	if (_commonFactor != 1 && _left != 0) {
		_left /= _commonFactor;
		_right /= _commonFactor;
	}
	if (abs(_left) == 1 && _right.getWhole() == 1 && _isImaginary) {
		/* Factor out i if possible */
		_cfIsImag = true;
		_leftIsImag = true;
		_right.setType(SquareRoot::Type::real);

		_left = -_left;
	}
}

void	CompoundSolution::adjustOrder() {
	if (_left < 0) {
		if (_sign == '+' || _commonFactor != 1) {
			_left = abs(_left);
			char nw_sign = _sign == '+' ? '-' : '+';

			// Reverse order (-n + m) => (m - n)
			if (_sign == '+') {
				_sign = nw_sign;
				_rev = true;
			}
			else {
				_sign = nw_sign;
				_commonFactor = -_commonFactor;
			}
		}
	}
}

CompoundSolution::operator	std::string() const {
	std::string imag = "𝑖";

	std::string cf = [=](){
		std::string res = "";
		if (_commonFactor != 1) { res += (std::string)_commonFactor; }
		if (_cfIsImag) { res += imag; }
		return res;
	}();

	std::string lft = [=](){
		std::string res = "";
		if (_left != 0) {
			if (_leftIsImag) {
				if (_left == -1) {
					res += "-";
				}
				res += imag;
			}
			else {
				res += (std::string)_left;
			}
		}
		return res;
	}();

	std::string fctrs = [=](){
		std::string res = "";
		std::string s(1, _sign);

		if (_rev) {
			res += (std::string)_right + s + lft;
		}
		else {
			res += lft + s + (std::string)_right;
		}
		return res;
	}();

	std::string sol = [=](){
		std::string res = cf;
		if (!cf.empty()) {
			res += "(";
		}
		res += fctrs;
		if (!cf.empty()) {
			res += ")";
		}
		return res;
	}();
	return sol;
}

std::ostream    		&operator<<(std::ostream &os, const CompoundSolution &x) {
	os << (std::string)x;
	return os;
}

CompoundSolutions::CompoundSolutions(Rational l, SquareRoot r):
_plus{CompoundSolution('+', l, r)}, _min{CompoundSolution('-', l, r)} {
	// _plus = CompoundSolution('+', l, r);
	// _min = CompoundSolution('-', l, r);
}

std::pair<std::string, std::string> CompoundSolutions::toStrings() const {
	return std::make_pair((std::string)_plus, (std::string)_min);
}

std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x) {
	auto [plus, min] = x.toStrings();
	os << plus << "\n" << min;
	return os;
}

SimpleSolutions::SimpleSolutions(Rational l, Rational r) {
	_plus = l + r;
	_min = l - r;
}

std::pair<std::string, std::string> SimpleSolutions::toStrings() const {
	return std::make_pair((std::string)_plus, (std::string)_min);
}

Solution::Solution(Rational l, SquareRoot r, size_t degree) : _degree{degree}, _num_print_solutions{2} {
	if (degree < 1 || degree > 2) {
		std::cout << "Degree of solution has to be 1 or 2. Using default degree of 2.\n";
		_degree = 2;
	}
	if (l != 0) {
		if (r.hasRealNumericSolution() || l.isFloating()) {
			_sol = SimpleSolutions(l, r.getNumericalSolution());
		}
		else {
			_sol = CompoundSolutions(l, r);
		}
	}
	else {
		// if (r.hasRealNumericSolution()) {
		// 	_num_print_solutions = 1;
		// 	std::cout << "Real numerical make abs\n";
		// 	_sol = abs(r.getNumericalSolution());
		// }
		// else {
		_num_print_solutions = 1;
		_sol = r;
		// }
	}
}

Solution::Solution(Rational sol, size_t degree): _sol{sol}, _degree{degree}, _num_print_solutions{1} {
	// In case of first degree solution or discriminant 0
	if (degree < 1 || degree > 2) {
		std::cout << "Degree of solution has to be 1 or 2. Using default degree of 1.\n";
		_degree = 1;
	}
	if (_degree == 2) {
		/* Means the discriminant was zero */ 
		_sol = abs(sol);
	}
}

std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x) {
	os << (std::string)x._plus << "\n" << (std::string)x._min;
	return os;
}

std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
	if (x._num_print_solutions == 2) {
		os << "Solutions:\n";
	}
	else {
		os << "Solution:\n";
	}
	if (x._num_print_solutions == 1 && x._degree == 2
	&& !(std::holds_alternative<Rational>(x._sol) && std::get<Rational>(x._sol) == 0)) {
		os << "+/-";
	}
	std::visit([&](auto arg){
		os << arg;
	}, x._sol);
	return os;
}
