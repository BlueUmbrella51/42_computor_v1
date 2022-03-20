#ifndef NUMBER_H
#define NUMBER_H
#include <variant>
#include "Rational.h"
#include "math_helpers.h"

typedef	std::variant<int, long, long long, float, double, long double, Rational> number;

class Number {
	public:
		number	_val;
		Number(number n);
		Number(Rational n);
		template<typename T,
			typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true
		>
		Number(T n) : _val{number(n)}{}
		Number(const Number &rhs);
		Number	&operator=(const Number &rhs);
	friend Number				operator*(const Number &a, const Number &b);
	friend Number				operator/(const Number &a, const Number &b);
	friend Number				operator+(const Number &a, const Number &b);
	// friend number			operator-(const  number &a, const  number &b);
	friend std::ostream    		&operator<<(std::ostream &os, const Number &x);
};

Number	getGcd(const Number &a, const Number &b);

#endif
// #ifndef NUMBER_H
// #define NUMBER_H
// #include <variant>
// #include <type_traits>
// #include "Rational.h"
// #include "Complex.h"
// #include "math_helpers.h"

// typedef 	std::variant<float, double, long double, Rational> number;

// class Number {
// 	private:
// 		number		_val;
	
// 	public:
// 		Number(number n);
// 		Number(long long int);
// 		~Number();
// 		Number				&operator*=(const Number &n);
// 		Number				&operator/=(Number &n);
// 		Number				&operator+=(Number &n);
// 		Number				&operator-=(Number &n);

// 	friend Number			operator*(Number &a, Number &b);
// 	friend Number			operator/(Number &a, Number &b);
// 	friend Number			operator+(Number &a, Number &b);
// 	friend Number			operator-(Number &a, Number &b);
// 	friend std::ostream    	&operator<<(std::ostream &os, const Number &x);
// 	friend bool            	operator==(const Number &lhs, const Number &rhs);
// 	friend Number			getGcd(Number &lhs, Number &rhs);
// };

/* Prevent floating point numbers from attempting to find GCD */

// template <typename T, typename U, typename = std::enable_if<std::is_integral<T>::value
// && std::is_integral<U>::value>>
// long long		getGcd(U n, T m);

// template <typename T, typename U, typename = std::enable_if<std::is_floating_point<T>::value 
// || std::is_floating_point<U>::value>>
// long long		getGcd(T n, U m);	

// #endif
