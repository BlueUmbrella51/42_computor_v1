#ifndef SOLUTION_H
#define SOLUTION_H
#include "Rational.h"
#include "Root.h"
#include <optional>

class Solution {
	public:
		enum	Order {
			standard, reversed
		};
		enum	Sign {
			plus, minus
		};
		Solution(Sign sign, Rational left, Root right);
		operator	std::string() const;
		void		factor();
		void		adjustOrder();
		void		getNumericalSolution();

	private:
		Sign					_sign;
		Order					_order;
		Rational 				_num;
		Root					_root;
		Root::Type				_type;
		Rational				_gcd;
		bool					_gcdIsImag;
		bool					_numIsImag;
		bool					_factored;
		std::optional<Rational> _solution;

	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
	// friend bool					operator==(const Solution &lhs, const Solution &rhs);
};

#endif