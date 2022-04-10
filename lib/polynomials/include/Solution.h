#ifndef SOLUTION_H
#define SOLUTIION_H
#include "Rational.h"
#include "Root.h"

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

	private:
		Sign		_sign;
		Order		_order;
		Rational 	_num;
		Root		_root;
		Root::Type	_type;
		Rational	_gcd;
		bool		_gcdIsImag;
		bool		_numIsImag;
		bool		_factored;

	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
};

#endif