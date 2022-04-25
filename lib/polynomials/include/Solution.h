#ifndef SOLUTION_H
#define SOLUTION_H
#include "Rational.h"
#include "SquareRoot.h"
#include <optional>
#include <variant>

class	CompoundSolution {
	/* Root wasn't expressable as numeric, or part is imaginary */
	public:
		CompoundSolution(char sign, Rational left, SquareRoot right);
		operator	std::string() const;
		void		factor();
		void		adjustOrder();
		SquareRoot	getRight() const;

	private:
		char		_sign;
		Rational	_left;
		bool		_leftIsImag;
		SquareRoot	_right;
		Rational	_commonFactor;
		bool		_cfIsImag;
		bool		_rev;
	
	friend bool					operator==(const CompoundSolution &lhs, const CompoundSolution &rhs);
	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolution &x);
};

class	CompoundSolutions {
	public:
		CompoundSolutions(Rational l, SquareRoot r);
		~CompoundSolutions() = default;
		int			getNumSolutions() const;
		std::pair<std::string, std::optional<std::string>> toStrings() const;
	
	private:
		CompoundSolution	_plus;
		CompoundSolution	_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x);
};

class	SimpleSolutions {
	public:
		SimpleSolutions();
		SimpleSolutions(Rational l, Rational r);
		SimpleSolutions(Rational sol);
		~SimpleSolutions() = default;
		int			getNumSolutions() const;
		std::pair<std::string, std::optional<std::string>> toStrings() const;
	
	private:
		Rational					_plus;
		std::optional<Rational>		_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
};

typedef	std::variant<SimpleSolutions, CompoundSolutions> solution;

class Solution {
	public:
		Solution() = default;
		Solution(Rational l, SquareRoot r);
		Solution(Rational sol);
		~Solution() = default;
		operator std::string() const;
		int		getNumSolutions() const;
	
	private:
		solution 	_sol;
	
	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
};

#endif
