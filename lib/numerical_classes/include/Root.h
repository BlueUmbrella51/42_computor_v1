#ifndef ROOT_H
#define ROOT_H
#include <variant>
#include <vector>
#include <iostream>
#include "Rational.h"
#include "math_helpers.h"

class	Root {
	public:
		enum Type {
			real,
			imaginary
		};
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Root(T d, int degree = 2) : _root{d}, _whole{1}, _degree{degree},
		_type{Root::Type::real}, _divisor{1} {
			if (_root < 0) {
				_type = Type::imaginary;
				_root = abs(_root);
			}
			simplifyNumerical(_root);
		}
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Root(long long w, T r, int degree = 2) : _root{r}, _whole{w}, _degree{degree}, 
		_type{Root::Type::real}, _divisor{1} {
			if (_root < 0) {
				_type = Type::imaginary;
				_root = abs(_root);
			}
		}
		Root(Rational n, int degree = 2);
		// Root(Fraction n, int degree = 2);
		Root	&operator=(const Root &rhs);
		~Root() = default;

		void		simplify(Rational &r);
		void		simplifyFraction(Fraction &n);
		void		simplifyNumerical(Numerical &n);
		Numerical	getRoot() const;
		Rational	getWhole() const;
		int			getDegree() const;
		Type		getType() const;
		void		setType(Type t);
		Rational	getDivisor() const;
		bool		isFloating() const;
		operator	std::string () const;
		operator 	long double () const;
		Root		&operator+=(const Root &rhs);
		Root		&operator-=(const Root &rhs);
		Root		&operator*=(const Root &rhs);
		Root		&operator/=(const Root &rhs);
		Root		&operator/=(const Rational &rhs);

	private:
		Numerical	_root;
		Rational	_whole;
		int			_degree;
		Type		_type;
		Rational	_divisor;
	
	friend std::ostream    		&operator<<(std::ostream &os, const Root &x);
	template<typename T, 
			typename std::enable_if<
            std::is_floating_point<T>{}, bool>::type = true
		>
	std::pair<long long, long double>		simplify_root(T n, int degree) {
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

	// friend void				simplify_root(Root &r, Numerical n, int degree);
	// friend void				simplify_root(Root &r, Fraction n, int degree);
	friend void				rationalize(Root &numer, const Root &denom);
	friend Root				operator/(const Root &lhs, const Rational &rhs);
	friend std::ostream    	&operator<<(std::ostream &os, const numerical &x);
};

Root		operator*(const Root &lhs, const Root &rhs);

bool		sameTypeAndRoot(const Root &lhs, const Root &rhs);
bool		operator==(const Root &lhs, const Root &rhs);
bool		operator!=(const Root &lhs, const Root &rhs);
#endif