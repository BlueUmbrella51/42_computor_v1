#include "Solution.h"

void	Solution::adjustOrder() {
	if (_num < 0) {
		_num = abs(_num);
		Sign nw_sign = _sign == Sign::plus ? Sign::minus : Sign::plus;

		if (_order == Order::standard) {
			if (_sign == Sign::plus) {
				_order = Order::reversed;
			}
			else {
				_gcd = -_gcd;
			}
		}
		_sign = nw_sign;
	}
}

void	Solution::factor() {
	_num /= _gcd;
	_root /= _gcd;
	adjustOrder();
}

Solution::Solution(Sign sign, Rational left, Root right):
_sign{sign}, _order{Order::standard}, _num{left}, _root{right},
_type{right.getType()}, _gcdIsImag{false}, _numIsImag{false}, _factored{false} {
	// TODO If anything is a float, just make everything a float
	// If not root, numerical solution can be found (check for imaginary)
	if (_root.getRoot() == 1) {
		std::cout << "Can be numerically solved:\n" << _num + _root.getWhole() << "\n" << _num - _root.getWhole() << "\n";
	}
	_gcd = getGcd(_num, _root.getWhole());
	if (_gcd != 1 && _num != 0) {
		_factored = true;
		factor();
		if ((_num == 1 || _num == -1) && _root.getWhole() == 1) {
		/* Left can become i or -i, so we can factor out i to a common factor */
			_root.setType(Root::Type::real);
			_gcdIsImag = true;
			_numIsImag = true;

			/* i * i = -1, i * -i = 1*/
			if (_num == -1) {
				/* if left is -1, factor becomes i */
				_num = 1;
			}
			else {
				/* if left is 1, factor becomes -i */
				_num = -1;
			}
			adjustOrder();
		}
	}
}

Solution::operator std::string() const {
	std::string sign = _sign == Solution::Sign::minus ? "-" : "+";
	std::string res = "";
	std::string root = (std::string)_root;
	std::string num = (std::string)_num;
	std::string gcd = (std::string)_gcd;

	if (_factored) {
		res += gcd;
		if (_gcdIsImag) {
			res += "i";
		}
		res += "(";
		if (_order == Order::reversed) {
			res += root + sign;
		}
		if (_numIsImag) {
			if (_num < 0) {
				res += "-i";
			}
			else {
				res += "i";
			}
		}
		else {
			res += num;
		}
		if (_order == Order::standard) {
			res += sign + root;
		}
		res += ")";
	}
	else {
		if (_num != 0) {
			res += num;
		}
		res += sign + root;
	}
	return res;
}

std::ostream    		&operator<<(std::ostream &os, const Solution &x) {
	os << (std::string)x;
	return os;
}
