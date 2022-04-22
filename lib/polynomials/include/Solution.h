#ifndef SOLUTION_H
#define SOLUTION_H
#include "Rational.h"
#include "SquareRoot.h"
#include <optional>
#include <variant>

#define IMAG "𝑖"

// typedef std::variant<Rational, SquareRoot>	parts;

// class 	CompoundSolution {
// 	public:
// 		CompoundSolution(char sign, Rational l, SquareRoot r);
// 		~CompoundSolution() = default;
// 		operator	std::string() const;

// 	private:
// 		char		_sign;
// 		bool		_isImaginary;
// 		Rational 	_commonFactor;
// 		bool		_cfIsImag;
// 		Rational 	_left;
// 		bool		_leftIsImag;
// 		SquareRoot	_right;
// 		bool		_rev;

// 		void	factor();
// 		void	adjustOrder();
	
// 	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolution &x);
// };

// class	CompoundSolutions {
// 	public:
// 		CompoundSolutions(Rational l, SquareRoot r);
// 		~CompoundSolutions() = default;
// 		std::pair<std::string, std::string> toStrings() const;
// 	private:
// 		CompoundSolution	_plus;
// 		CompoundSolution	_min;
	
// 	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x);
// };

// class	SimpleSolutions {
// 	public:
// 		// SimpleSolutions() = default;
// 		SimpleSolutions(Rational l, Rational r);
// 		SimpleSolutions(Rational sol);
// 		~SimpleSolutions() = default;
// 		std::pair<std::string, std::string> toStrings() const;
// 	private:
// 		Rational	_plus;
// 		Rational	_min;
	
// 	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
// };

// typedef	std::variant<Rational, SquareRoot, SimpleSolutions, CompoundSolutions>	solution;

// class	Solution {
// 	public:
// 		Solution() = default;
// 		Solution(Rational l, SquareRoot r, size_t degree = 2);
// 		Solution(Rational sol, size_t degree);
// 		operator std::string() const;
	
// 	private:
// 		solution 	_sol;
// 		size_t		_degree;
// 		size_t		_num_print_solutions;
// 		bool		_num_from_root;
// 		void		getNumericalSolutions();
	
// 	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
// };

// class ImagSolution {
// 	public:
// 		ImagSolutions();
	
// 	private:
// 		std::optional<Rational> 	_plus;
// 		std::optional<SquareRoot>	_sol2;
// }

// class RealSolutions {
// 	public:
// 		RealSolutions(Rational l, Rational r);
// 		RealSolutions(Rational sol);
	
// 	private:
// 		Rational 				_plus;
// 		std::optional<Rational>	_sol2;
// }

class	CompoundSolution {
	/* Root wasn't expressable as numeric, or part is imaginary */
	public:
		CompoundSolution(char sign, Rational left, SquareRoot right);
		operator	std::string() const;
		void		factor();
		void		adjustOrder();

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
		std::pair<std::string, std::string> toStrings() const;
	
	private:
		CompoundSolution	_plus;
		CompoundSolution	_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const CompoundSolutions &x);
};

class	SimpleSolutions {
	public:
		SimpleSolutions();
		SimpleSolutions(Rational l, Rational r);
		~SimpleSolutions() = default;
		std::pair<std::string, std::string> toStrings() const;
	private:
		Rational	_plus;
		Rational	_min;
	
	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
};

// class	SimpleSolution {
// 	public:
// 		SimpleSolution(Rational n);
// 		operator std::string() const;
	
// 	private:
// 		Rational	_sol;
	
// 	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
// };

// class	RootOnlySolution {
// 	public:
// 		RootOnlySolution(SquareRoot s);
// 		operator std::string() const;
	
// 	private:
// 		SquareRoot	_sol;

// 	friend std::ostream    		&operator<<(std::ostream &os, const SimpleSolutions &x);
// };

typedef	std::variant<SimpleSolutions, CompoundSolutions> solution;

class Solution {
	public:
		Solution() = default;
		Solution(Rational l, SquareRoot r);
		Solution(Rational sol, bool imag);
		~Solution() = default;
		operator std::string() const;
	
	private:
		solution _sol;
		size_t	_num_solutions;
	
	friend std::ostream    		&operator<<(std::ostream &os, const Solution &x);
};

#endif
