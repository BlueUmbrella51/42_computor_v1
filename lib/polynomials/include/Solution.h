#ifndef SOLUTION_H
#define SOLUTION_H
#include "Rational.h"
#include "SquareRoot.h"
#include <optional>
#include <variant>

typedef std::variant<Rational, SquareRoot>	parts;

class 	CompoundSolution {
	public:
		CompoundSolution(char sign, Rational l, SquareRoot r);
		~CompoundSolution() = default;
		operator	std::string() const;

	private:
		char		_sign;
		bool		_isImaginary;
		Rational 	_commonFactor;
		bool		_cfIsImag;
		Rational 	_left;
		bool		_leftIsImag;
		SquareRoot		_right;
		bool		_rev;

		void	factor();
		void	adjustOrder();
	
	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolution &x);
};

class	CompoundSolutions {
	public:
		CompoundSolutions(Rational l, SquareRoot r);
		~CompoundSolutions() = default;
		std::pair<std::string, std::string> toStrings() const;
	private:
		CompoundSolution	_plus;
		CompoundSolution	_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x);
};

class	SimpleSolutions {
	public:
		SimpleSolutions() = default;
		SimpleSolutions(Rational l, Rational r);
		~SimpleSolutions() = default;
		std::pair<std::string, std::string> toStrings() const;
	private:
		Rational	_plus;
		Rational	_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
};

typedef	std::variant<SimpleSolutions, CompoundSolutions>	solution;

class	Solution {
	public:
		Solution() = default;
		Solution(Rational l, SquareRoot r);
	
	private:
		solution _sol;
		void	getNumericalSolutions();
	
	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
};

#endif
