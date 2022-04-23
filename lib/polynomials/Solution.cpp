#include "Solution.h"

void	CompoundSolution::factor() {
	/* Factor out any common factors */
	_commonFactor = getGcd(_left, _right.getWhole());
	if (_commonFactor != 1 && _left != 0) {
		_left /= _commonFactor;
		_right /= _commonFactor;
	}
	if (abs(_left) == 1 && abs(_right.getWhole()) == 1 && _right.isImaginary()) {
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
;	std::string cf = [=](){
		std::string res = "";
		if (_commonFactor != 1) { res += (std::string)_commonFactor; }
		if (_cfIsImag) { res += IMAG; }
		return res;
	}();

	std::string lft = [=](){
		std::string res = "";
		if (_left != 0) {
			if (_leftIsImag) {
				if (_left == -1) {
					res += "-";
				}
				res += IMAG;
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

		if (_left != 0) {
			if (_rev) {
				res += (std::string)_right + s + lft;
			}
			else {
				res += lft + s + (std::string)_right;
			}
		}
		else {
			res += (std::string)_right;
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

bool					operator==(const CompoundSolution &lhs, const CompoundSolution &rhs) {
	/* Two solutions are considered "equal" if only their signs differ, so if left == 0*/
	return (lhs._left == rhs._left && lhs._left == 0
	&& lhs._right == rhs._right);
}

SquareRoot 		CompoundSolution::getRight() const {
	return _right;
}

CompoundSolution::CompoundSolution(char sign, Rational left, SquareRoot right):
_sign{sign}, _left{left}, _leftIsImag{false}, _right{right}, _commonFactor{1},
_cfIsImag{false}, _rev{false} {
	// - Real solutions with root in answer
	// - Imaginary solutions (with or without root in answer)
	if (_left.isFloating() || _right.hasNumericSolution()) {
		/* We are dealing with a numeric solution of an imaginary root */
		_right.toNumerical();
	}
	if (_left != 0) {
		factor();
		adjustOrder();
	}
}

CompoundSolutions::CompoundSolutions(Rational l, SquareRoot r):
_plus{CompoundSolution('+', l, r)}, _min{CompoundSolution('-', l, r)} {
}

std::pair<std::string, std::optional<std::string>> CompoundSolutions::toStrings() const {
	if (_plus == _min) {
		if (_plus.getRight() == SquareRoot(0)) {
			return (std::make_pair("0", std::nullopt));
		}
		return std::make_pair("+/-" + (std::string)_plus, std::nullopt);
	}
	return std::make_pair((std::string)_plus, (std::string)_min);
}

int			CompoundSolutions::getNumSolutions() const {
	if ((_plus == _min && _plus.getRight() == SquareRoot(0))) {
		return 1;
	}
	return 2;
}

std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x) {
	auto [plus, min] = x.toStrings();
	os << plus;
	if (min) {
		os  << "\n" << min.value();
	}
	return os;
}

std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x) {
	auto [ plus, min ] = x.toStrings();
	os << plus;
	if (min) {
		os << "\n" << min.value();
	}
	return os;
}

std::pair<std::string, std::optional<std::string>> SimpleSolutions::toStrings() const {
	if (!_min) {
		return make_pair((std::string)_plus, std::nullopt);
	}
	if (_plus == _min.value()) {
		std::cout << "Same answer simple\n";
		if (_plus == 0) {
			return std::make_pair("0", std::nullopt);
		}
		return std::make_pair("+/-" + (std::string)_plus, std::nullopt);
	}
	return std::make_pair((std::string)_plus, (std::string)_min.value());
}

int			SimpleSolutions::getNumSolutions() const {
	if (!_min || (_plus == _min.value() && _plus == 0)) {
		return 1;
	}
	return 2;
}

SimpleSolutions::SimpleSolutions(): _plus{0}, _min{0}{}

SimpleSolutions::SimpleSolutions(Rational sol): _plus{sol}, _min{std::nullopt} {}

SimpleSolutions::SimpleSolutions(Rational l, Rational r) {
	/* Only for REAL and distinct answers */
	_plus = l + r;
	_min = l - r;

	// if (abs(_plus) - (long long)abs(_plus) == 0) {
	// 	_plus = (long long)_plus;
	// }
	// if (_min && abs(_min.value()) - (long long)abs(_min.value()) == 0) {
	// 	_min = (long long)_min.value();
	// }
	std::cout << "Simple solutions " << (std::string)_plus << "  " << (std::string)_min.value() << "\n";

	if (abs(_plus) == abs(_min.value())) {
		_plus = abs(_plus);
		_min = _plus;
	}
}



// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Solution::operator std::string() const {
	return std::visit(overloaded {
		[=](CompoundSolutions arg){ 
			auto [ left, right ] = arg.toStrings();
			std::string result = left;//std::get<0>(res) + "\n" + std::get<1>(res);
			if (right) {
				result += "\n" + right.value();
			}
			return result;
		},
		[](SimpleSolutions arg) {
			auto [ left, right ] = arg.toStrings();
			std::string result = left;//std::get<0>(res) + "\n" + std::get<1>(res);
			if (right) {
				result += "\n" + right.value();
			}
			return result;
		}
	}, _sol);
}

int		Solution::getNumSolutions() const {
	return std::visit(overloaded {
		[](CompoundSolutions arg){ 
			return arg.getNumSolutions();
		},
		[](SimpleSolutions arg) {
			return arg.getNumSolutions();
		}
	}, _sol);
}

std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
	int	num_solutions = x.getNumSolutions();

	if (num_solutions == 2) {
		os << "The solutions are:\n";
	}
	else {
		os << "The solution is:\n";
	}
	os << (std::string)x;
	return os;
}

Solution::Solution(Rational sol) {
	_sol = SimpleSolutions(sol);
}

Solution::Solution(Rational l, SquareRoot r) {
	// if (l.isFloating() && abs(l) - (long long)abs(l) == 0) {
	// 	l = (long long)l;
	// }
	// std::cout << "SOLUTION: " << (std::string)l << "  " << (std::string)r << "\n";
	// if (r.getSquareRoot() == 0) {
	// 	/* Only left matters: unique real solution */
	// 	std::cout << "Only left matters\n";
	// 	_sol = CompoundSolutions(l, r);
	// 	// Only left matters
	// }
	// else if (l != 0) {
	// 	_num_solutions = 2;
		/* Left side (b^2/2a0 is not zero: we have to distinct solutions */
	if (r.hasRealNumericSolution()) {
		/* Only for REAL solutions with a numerical solution (no root in in answer) 
		where -b^2/2a != 0*/
		Rational right = r.getNumericalSolution();

		if (r != 0)
			_sol = SimpleSolutions(l, r.getNumericalSolution());
		else {
			_sol = SimpleSolutions(l);
		}
	}
	else {
		/* For:
		- Real solutions with root in answer
		- Imaginary solutions (with or without root in answer)
		where -b^2/2a != 0
		*/
		_sol = CompoundSolutions(l, r);
	}
	// }
	// else {
	// 	/* We have two distinct solutions that are the same but negative and positive 
	// 	Only the root matters in this case since left = 0. Can be real/imaginary,
	// 	contain a root or be numerical;
	// 	*/
	// 	_num_solutions = 2;
	// 	std::cout << "Same solution but + or -\n";
	// 	// if (r.hasRealNumericSolution()) {
	// 	// 	/* Root is perfect square OR floating point value */
	// 	// 	_num_print_solutions = 1;
	// 	// 	/* We need to indicate that this WAS a root so we know we still deal with two 
	// 	// 	distinct solutions */
	// 	// 	_num_from_root = true;
	// 	// 	_sol = abs(r.getNumericalSolution());
	// 	// }
	// 	// else {
	// 	// 	/* Plus or minus root is answer */
	// 	// 	_num_print_solutions = 1;
	// 	// 	_sol = r;
	// }
}
