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

Solution::Solution(Rational l, SquareRoot r) {
	if (r.hasRealNumericSolution() || l.isFloating()) {
		_sol = SimpleSolutions(l, r.getNumericalSolution());
	}
	else {
		_sol = CompoundSolutions(l, r);
	}
}

std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x) {
	os << (std::string)x._plus << "\n" << (std::string)x._min;
	return os;
}

Solution::operator std::string() const {
	return std::visit([](auto arg) {
		return (std::string)arg;
	}, _sol);
}

std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
	std::visit([&](auto arg){
		os << arg;
	}, x._sol);
	return os;
}

// void	Solution::adjustOrder() {
// 	if (_num < 0) {
// 		_num = abs(_num);
// 		Sign nw_sign = _sign == Sign::plus ? Sign::minus : Sign::plus;

// 		if (_order == Order::standard) {
// 			if (_sign == Sign::plus) {
// 				_order = Order::reversed;
// 			}
// 			else {
// 				_gcd = -_gcd;
// 			}
// 		}
// 		_sign = nw_sign;
// 	}
// }

// void	Solution::factor() {
// 	_num /= _gcd;
// 	_root /= _gcd;
// 	adjustOrder();
// }

// void	Solution::getNumericalSolution() {
// 	Rational s = _root.getNumericalSolution();

// 	_solution = _sign == Sign::plus ? _num + s : _num - s;
// }

// Solution::Solution(Sign sign, Rational left, SquareRoot right):
// _sign{sign}, _order{Order::standard}, _num{left}, _root{right},
// _type{right.getType()}, _gcdIsImag{false}, _numIsImag{false}, _factored{false},
// _solution{std::nullopt} {
// 	// TODO If anything is a float, just make everything a float
// 	// If not root, numerical solution can be found (check for imaginary)
// 	// NUM is 0
// 	if (_root.hasNumericSolution() || _num.isFloating()) {
// 		getNumericalSolution();
// 		// std::cout << "Has purely numerical solution";
// 		_solution =  _root.getNumericalSolution();//_root.getNumericalSolution();
// 		// std::cout << _num + _solution.value() << "\n" << _num - _solution.value() << "\n";
// 	}
// 	// if (_num == 0) {
// 	// 	// +/ _root is solution
// 	// 	std::cout << "b is 0\n" << "+/-" << (_solution? _solution.value() : _root) << "\n";
// 	// }
// 	// if (_root.getSquareRoot() == 1) {
// 	// 	std::cout << "Can be numerically solved:\n" << _num + _root.getWhole() << "\n" << _num - _root.getWhole() << "\n";
// 	// }
// 	else {
// 		_gcd = getGcd(_num, _root.getWhole());
// 		if (_gcd != 1 && _num != 0) {
// 			_factored = true;
// 			factor();
// 			if ((_num == 1 || _num == -1) && _root.getWhole() == 1 && _root.getType() == SquareRoot::Type::imaginary) {
// 			/* Left can become i or -i, so we can factor out i to a common factor */
// 				_root.setType(SquareRoot::Type::real);
// 				_gcdIsImag = true;
// 				_numIsImag = true;

// 				/* i * i = -1, i * -i = 1*/
// 				if (_num == -1) {
// 					/* if left is -1, factor becomes i */
// 					_num = 1;
// 				}
// 				else {
// 					/* if left is 1, factor becomes -i */
// 					_num = -1;
// 				}
// 				adjustOrder();
// 			}
// 		}
// 	}
// }

// Solution::operator std::string() const {
// 	std::string sign = _sign == Solution::Sign::minus ? "-" : "+";
// 	std::string res = "";
// 	std::string root = (std::string)_root;
// 	std::string num = (std::string)_num;
// 	std::string gcd = (std::string)_gcd;

// 	// if (_num == 0) {
// 	// 	if (_solution) {
// 	// 		res += "+/-" + (std::string)_solution.value();
// 	// 	}
// 	// 	else {
// 	// 		res 
// 	// 	}
// 	// }
// 	std::string imag = "𝑖";
// 	if (_solution) {
// 		/* change signs! */
// 		Rational s = _solution.value();

// 		if (s < 0 && _sign == Sign::minus) {
// 			res += "+" + (std::string)abs(s);
// 		}
// 		else if (s < 0 && _sign == Sign::plus) {
// 			res += (std::string)s;
// 		}
// 		else {
// 			res += sign + (std::string)s;
// 		}
// 	}
// 	else if (_factored) {
// 		res += gcd;
// 		if (_gcdIsImag) {
// 			res += imag;
// 		}
// 		res += "(";
// 		if (_order == Order::reversed) {
// 			res += root + sign;
// 		}
// 		if (_numIsImag) {
// 			if (_num < 0) {
// 				res += "-" + imag;
// 			}
// 			else {
// 				res += imag;
// 			}
// 		}
// 		else {
// 			res += num;
// 		}
// 		if (_order == Order::standard) {
// 			res += sign + root;
// 		}
// 		res += ")";
// 	}
// 	else {
// 		if (_num != 0) {
// 			res += num;
// 		}
// 		res += sign + root;
// 	}
// 	return res;
// }

// std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
// 	os << (std::string)x;
// 	return os;
// }
