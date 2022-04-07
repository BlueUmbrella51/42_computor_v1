#ifndef ROOT_H
#define ROOT_H
#include <variant>
#include <vector>
#include <iostream>
#include "Numerical.h"

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
			simplify();
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
		Root(Numerical n, int degree = 2);
		Root	&operator=(const Root &rhs);
		~Root() = default;

		void		simplify();
		Numerical	getRoot() const;
		long long	getWhole() const;
		int			getDegree() const;
		Type		getType() const;
		Numerical	getDivisor() const;
		Root		&operator+=(const Root &rhs);
		Root		&operator-=(const Root &rhs);
		Root		&operator*=(const Root &rhs);
		Root		&operator/=(const Root &rhs);

	private:
		Numerical	_root;
		long long	_whole;
		int			_degree;
		Type		_type;
		Numerical	_divisor;
	
	friend std::ostream    		&operator<<(std::ostream &os, const Root &x);
	// friend std::ostream    		&operator<<(std::ostream &os, const numerical &x);
};

Root		operator*(const Root &lhs, const Root &rhs);

bool		sameTypeAndRoot(const Root &lhs, const Root &rhs);
bool		operator==(const Root &lhs, const Root &rhs);
bool		operator!=(const Root &lhs, const Root &rhs);

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
	long long 	prime = 2;
	long long	whole = 1;
	long long 	radical = 1;

	std::vector<std::pair<long long, long long>> factors = {};
	while (n >= prime * prime) {
		if (n % prime == 0) {
			if (!factors.empty() && std::get<0>(factors.back()) == prime) {
				std::get<1>(factors.back()) += 1;
			}
			else {
				factors.push_back(std::make_pair(prime, 1));
			}
			n /= prime;
		}
		else {
			// count = 0;
			++prime;
		}
	}
	if (!factors.empty() && std::get<0>(factors.back()) == n) {
		std::get<1>(factors.back()) += 1;
	}
	else {
		factors.push_back(std::make_pair(n, 1));
	}
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
		std::cout << factor << " " << degr << "\n";
	}
	return std::make_pair(whole, radical);
}

#endif