#ifndef SQUARE_ROOT_H
#define SQUARE_ROOT_H
#include <variant>
#include <vector>
#include <iostream>
#include "Rational.h"

/* Class to represent Roots. Currently for degree 2 only. Not all operations
take into account the type of the root (real or imaginary), but in the way they are used now
that does not pose a problem (warning for future use/expansion) */
class	SquareRoot {
	public:
		enum Type {
			real,
			imaginary
		};
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		SquareRoot(long long w, T r) : _root{r}, _whole{w}, _degree{2}, 
		_type{SquareRoot::Type::real}, _divisor{1} {
			if (_root == 0) {
				std::cout << "Root cannot be zero, setting it to 1.\n";
				_root = 1;
			}
			if (_root < 0) {
				_type = Type::imaginary;
				_root = abs(_root);
			}
		}
		SquareRoot(Rational n);
		SquareRoot	&operator=(const SquareRoot &rhs);
		operator	std::string () const;
		~SquareRoot() = default;

		void		simplify(Rational &r);
		void		simplifyFraction(Fraction &n);
		void		simplifyNumerical(Numerical &n);
		Numerical	getSquareRoot() const;
		Rational	getWhole() const;
		int			getDegree() const;
		bool		isImaginary() const;
		bool		isReal() const;
		bool		isPerfect() const;
		Type		getType() const;
		void		setType(Type t);
		Rational	getDivisor() const;
		bool		isFloating() const;
		bool		hasNumericSolution() const;
		bool		hasRealNumericSolution() const;
		Rational	getNumericalSolution() const;
		operator	long double () const;
		SquareRoot		&toNumerical();
		SquareRoot		&operator+=(const SquareRoot &rhs);
		SquareRoot		&operator-=(const SquareRoot &rhs);
		SquareRoot		&operator*=(const SquareRoot &rhs);
		SquareRoot		&operator/=(const Rational &rhs);

	private:
		Numerical				_root;
		Rational				_whole;
		int						_degree;
		Type					_type;
		Rational				_divisor;
	
	friend std::ostream    		&operator<<(std::ostream &os, const SquareRoot &x);
	template<typename T, 
			typename std::enable_if<
            std::is_floating_point<T>{}, bool>::type = true
		>
	std::pair<long long, long double>		simplify_root(T n, int degree) {
		if ((long long)n == n) {
			return simplify_root((long long)n, degree);
		}
		return std::make_pair(1, n);
	}

	template<typename T, 
				typename std::enable_if<
				std::is_integral<T>{}, bool>::type = true
			>
	std::pair<long long, long long>		simplify_root(T n, int degree) {
		/* Any square sqrt(n) can be represented as sqrt(f1) * sqrt(f2).
		We are looking for the largest perfect square f1 */
		long long	whole = 1;
		long long 	radical = 1;

		auto factors = getPrimeFactors(n);
		for(auto i = factors.begin(); i != factors.end(); ++i) {
			auto factor = std::get<0>(*i);
			auto degr = std::get<1>(*i);

			while (degr >= degree) {
				degr -= degree;
				whole *= factor;
			}
			if (degr > 0) {
				radical *= factor;
			}
		}
		return std::make_pair(whole, radical);
	}

	friend void				rationalize(SquareRoot &numer, const SquareRoot &denom);
	friend SquareRoot				operator/(const SquareRoot &lhs, const Rational &rhs);
	friend std::ostream    	&operator<<(std::ostream &os, const numerical &x);
};

SquareRoot		operator*(const SquareRoot &lhs, const SquareRoot &rhs);

bool		sameTypeAndSquareRoot(const SquareRoot &lhs, const SquareRoot &rhs);
bool		operator==(const SquareRoot &lhs, const SquareRoot &rhs);
bool		operator!=(const SquareRoot &lhs, const SquareRoot &rhs);
#endif