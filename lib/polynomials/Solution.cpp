#include "Solution.h"

// CompoundSolution::CompoundSolution(char sign, Rational l, SquareRoot r) :
// _sign{sign}, _isImaginary{r.getType() == SquareRoot::Type::imaginary},
// _commonFactor{1}, _cfIsImag{false}, _left{l}, 
// _leftIsImag{false}, _right{r}, _rev{false} {
// 	if (_left != 0) {
// 		factor();
// 		adjustOrder();
// 	}
// }

// void	CompoundSolution::factor() {
// 	/* Factor out any common factors */
// 	_commonFactor = getGcd(_left, _right.getWhole());
// 	if (_commonFactor != 1 && _left != 0) {
// 		_left /= _commonFactor;
// 		_right /= _commonFactor;
// 	}
// 	if (abs(_left) == 1 && _right.getWhole() == 1 && _isImaginary) {
// 		/* Factor out i if possible */
// 		_cfIsImag = true;
// 		_leftIsImag = true;
// 		_right.setType(SquareRoot::Type::real);

// 		_left = -_left;
// 	}
// }

// void	CompoundSolution::adjustOrder() {
// 	if (_left < 0) {
// 		if (_sign == '+' || _commonFactor != 1) {
// 			_left = abs(_left);
// 			char nw_sign = _sign == '+' ? '-' : '+';

// 			// Reverse order (-n + m) => (m - n)
// 			if (_sign == '+') {
// 				_sign = nw_sign;
// 				_rev = true;
// 			}
// 			else {
// 				_sign = nw_sign;
// 				_commonFactor = -_commonFactor;
// 			}
// 		}
// 	}
// }

// CompoundSolution::operator	std::string() const {
// 	std::string cf = [=](){
// 		std::string res = "";
// 		if (_commonFactor != 1) { res += (std::string)_commonFactor; }
// 		if (_cfIsImag) { res += IMAG; }
// 		return res;
// 	}();

// 	std::string lft = [=](){
// 		std::string res = "";
// 		if (_left != 0) {
// 			if (_leftIsImag) {
// 				if (_left == -1) {
// 					res += "-";
// 				}
// 				res += IMAG;
// 			}
// 			else {
// 				res += (std::string)_left;
// 			}
// 		}
// 		return res;
// 	}();

// 	std::string fctrs = [=](){
// 		std::string res = "";
// 		std::string s(1, _sign);

// 		if (_rev) {
// 			res += (std::string)_right + s + lft;
// 		}
// 		else {
// 			res += lft + s + (std::string)_right;
// 		}
// 		return res;
// 	}();

// 	std::string sol = [=](){
// 		std::string res = cf;
// 		if (!cf.empty()) {
// 			res += "(";
// 		}
// 		res += fctrs;
// 		if (!cf.empty()) {
// 			res += ")";
// 		}
// 		return res;
// 	}();
// 	return sol;
// }

// std::ostream    		&operator<<(std::ostream &os, const CompoundSolution &x) {
// 	os << (std::string)x;
// 	return os;
// }

// CompoundSolutions::CompoundSolutions(Rational l, SquareRoot r):
// _plus{CompoundSolution('+', l, r)}, _min{CompoundSolution('-', l, r)} {

// }

// std::pair<std::string, std::string> CompoundSolutions::toStrings() const {
// 	return std::make_pair((std::string)_plus, (std::string)_min);
// }

// std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x) {
// 	auto [plus, min] = x.toStrings();
// 	os << plus << "\n" << min;
// 	return os;
// }

// SimpleSolutions::SimpleSolutions(Rational l, Rational r) {
// 	_plus = l + r;
// 	_min = l - r;
// }

// std::pair<std::string, std::string> SimpleSolutions::toStrings() const {
// 	return std::make_pair((std::string)_plus, (std::string)_min);
// }

// Solution::Solution(Rational l, SquareRoot r, size_t degree) : _degree{degree}, _num_print_solutions{2},
// _num_from_root{false} {
// 	if (degree < 1 || degree > 2) {
// 		std::cout << "Degree of solution has to be 1 or 2. Using default degree of 2.\n";
// 		_degree = 2;
// 	}
// 	if (l != 0) {
// 		/* Left side (b^2/2a0 is not zero: we have to distinct solutions */
// 		if (r.hasRealNumericSolution() || l.isFloating()) {
// 			/* Only for REAL solutions with a numerical solution (no root in inaswer) 
// 			where -b^2/2a != 0*/
// 			_sol = SimpleSolutions(l, r.getNumericalSolution());
// 		}
// 		else {
// 			/* For:
// 			- Real solutions with root in answer
// 			- Imaginary solutions
// 			where -b^2/2a != 0
// 			 */
// 			_sol = CompoundSolutions(l, r);
// 		}
// 	}
// 	else {
// 		/* We have two distinct solutions that are the same but negative and positive */
// 		if (r.hasRealNumericSolution()) {
// 			/* Root is perfect square OR floating point value */
// 			_num_print_solutions = 1;
// 			/* We need to indicate that this WAS a root so we know we still deal with two 
// 			distinct solutions */
// 			_num_from_root = true;
// 			_sol = abs(r.getNumericalSolution());
// 		}
// 		else {
// 			/* Plus or minus root is answer */
// 			_num_print_solutions = 1;
// 			_sol = r;
// 		}
// 	}
// }

// Solution::Solution(Rational sol, size_t degree): _sol{sol}, _degree{degree}, _num_print_solutions{1},
// _num_from_root{false} {
// 	// In case of first degree solution or discriminant 0, only one s
// 	if (degree < 1 || degree > 2) {
// 		std::cout << "Degree of solution has to be 1 or 2. Using default degree of 1.\n";
// 		_degree = 1;
// 	}
// 	if (_degree == 2) {
// 		/* Means the discriminant was zero */ 
// 		_sol = sol;
// 	}
// }

// std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x) {
// 	os << (std::string)x._plus << "\n" << (std::string)x._min;
// 	return os;
// }

// // helper type for the visitor #4
// template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// // explicit deduction guide (not needed as of C++20)
// template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// Solution::operator std::string() const {
// 	return std::visit(overloaded {
// 		[](CompoundSolutions arg){ 
// 			auto res = arg.toStrings();
// 			std::string result = std::get<0>(res) + "\n" + std::get<1>(res);
// 			return result;
// 		},
// 		[](SimpleSolutions arg) {
// 			auto res = arg.toStrings();
// 			std::string result = std::get<0>(res) + "\n" + std::get<1>(res);
// 			return result;
// 		},
// 		[=](SquareRoot arg) {
// 			std::string res = "";
// 			if (_num_print_solutions == 1 && _degree == 2) {
// 				res += "+/-";
// 			}
// 			res += (std::string)arg;
// 			return res;
// 		},
// 		[=](Rational arg) {
// 			std::cout << "Rational\n" << "nfr: " << _num_from_root << "\n";
// 			std::string res = "";
// 			if (arg != 0 && _num_from_root) {
// 				/* We only want this if the root part is purely numerical and left part was zero, 
// 				not if the b is the answer and the root was insignificant. */
// 				res += "+/-";
// 			}
// 			res += (std::string)arg;
// 			return res;
// 		}
// 	}, _sol);
// }

// std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
// 	if (x._num_print_solutions == 2) {
// 		os << "The solutions are:\n";
// 	}
// 	else {
// 		os << "The solution is:\n";
// 	}
// 	os << (std::string)x;
// 	return os;
// }

void	CompoundSolution::factor() {
	/* Factor out any common factors */
	_commonFactor = getGcd(_left, _right.getWhole());
	if (_left < 0 || _right.getWhole() < 0) {
		_commonFactor = -_commonFactor;
	}
	std::cout << "Gcd: " << _commonFactor << "\n";
	if (_commonFactor != 1 && _left != 0) {
		_left /= _commonFactor;
		_right /= _commonFactor;
	}
	std::cout << "left: " << _left << "\n";
	std::cout << "right: " << _right << " " << _right.getSquareRoot() << " " << _right.getWhole()  << "\n";
	if (abs(_left) == 1 && _right.getWhole() == 1 && _right.isImaginary()) {
		/* Factor out i if possible */
		_cfIsImag = true;
		_leftIsImag = true;
		_right.setType(SquareRoot::Type::real);
		std::cout << "right: " << _right << " " << _right.getSquareRoot() << " " << _right.getWhole()  << "\n";
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
	std::string cf = [=](){
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
	return (lhs._left == rhs._left && lhs._left == 0);
}

CompoundSolution::CompoundSolution(char sign, Rational left, SquareRoot right):
_sign{sign}, _left{left}, _leftIsImag{false}, _right{right}, _commonFactor{1},
_cfIsImag{false}, _rev{false} {
	std::cout << "Compound solution: " << _left << " " << _right << "\n";
	// - Real solutions with root in answer
	// - Imaginary solutions (with or without root in answer)
	if (_left != 0) {
		factor();
		adjustOrder();
	}
}

CompoundSolutions::CompoundSolutions(Rational l, SquareRoot r):
_plus{CompoundSolution('+', l, r)}, _min{CompoundSolution('-', l, r)} {

}

std::pair<std::string, std::string> CompoundSolutions::toStrings() const {
	if (_plus == _min) {
		std::cout << "Same answer compound\n";
		return std::make_pair("+/-" + (std::string)_plus, "");
	}
	return std::make_pair((std::string)_plus, (std::string)_min);
}

std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x) {
	auto [plus, min] = x.toStrings();
	os << plus << "\n" << min;
	return os;
}

std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x) {
	os << (std::string)x._plus << "\n" << (std::string)x._min;
	return os;
}

std::pair<std::string, std::string> SimpleSolutions::toStrings() const {
	return std::make_pair((std::string)_plus, (std::string)_min);
}

SimpleSolutions::SimpleSolutions(): _plus{0}, _min{0}{}

SimpleSolutions::SimpleSolutions(Rational l, Rational r) {
	/* Only for REAL and distinct answers */
	_plus = l + r;
	_min = l - r;
}



// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Solution::operator std::string() const {
	return std::visit(overloaded {
		[](CompoundSolutions arg){ 
			auto res = arg.toStrings();
			std::string result = std::get<0>(res) + "\n" + std::get<1>(res);
			return result;
		},
		[](SimpleSolutions arg) {
			auto res = arg.toStrings();
			std::string result = std::get<0>(res) + "\n" + std::get<1>(res);
			return result;
		}
	}, _sol);
}

std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
	if (x._num_solutions == 2) {
		os << "The solutions are:\n";
	}
	else {
		os << "The solution is:\n";
	}
	os << (std::string)x;
	return os;
}

Solution::Solution(Rational l, SquareRoot r) {
	if (l.isFloating() && (long long)l == l) {
		l = (long long)l;
	}
	// if (r.getSquareRoot() == 0) {
	// 	/* Only left matters: unique real solution */
	// 	std::cout << "Only left matters\n";
	// 	_sol = CompoundSolutions(l, r);
	// 	// Only left matters
	// }
	// else if (l != 0) {
	// 	_num_solutions = 2;
		/* Left side (b^2/2a0 is not zero: we have to distinct solutions */
	if (r.hasRealNumericSolution() || l.isFloating()) {
		/* Only for REAL solutions with a numerical solution (no root in in answer) 
		where -b^2/2a != 0*/
		_sol = SimpleSolutions(l, r.getNumericalSolution());
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
