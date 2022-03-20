#include <type_traits>

class Rational;
class Complex;

class Number {
	/* Governs interactions between Real and Complex numbers */
	public:
};

Number	operator*(const Rational &r, const Complex &c);
Number	operator*(const Complex &c, const Rational &r);
Number	operator/(const Rational &r, const Complex &c);
Number	operator/(const Complex &c, const Rational &r);
Number	operator+(const Rational &r, const Complex &c);
Number	operator+(const Complex &c, const Rational &r);
Number	operator-(const Rational &r, const Complex &c);
Number	operator-(const Complex &c, Rational &r);

class Real: Number  {
	/* Includes all Rational numbers and all Irrational number, governs interaction
	between Rationals and decimals / integrals (if not expressed as rationals) */
	// public:
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			multiply(Rational &r, T n) {
	// 		return (long double(r) * n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			multiply(T n, Rational &r) {
	// 		return 	multiply(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			divide(Rational &r, T n) {
	// 		return (long double(r) / n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			divide(T n, Rational &r) {
	// 		return divide(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			add(Rational &r, T n) {
	// 		return (long double(r) + n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			add(T n, Rational &r) {
	// 		return add(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			subtract(Rational &r, T n) {
	// 		return (long double(r) + n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			subtract(T n, Rational &r) {
	// 		return subtract(r, n);
	// 	}
};

class Rational : public Real {
	/* Represents all Rational numbers such as integrals and fractions
	that can be expressed a ratio between two integrals (i.e. -4/8, 4/1) */
	public:
		Rational(long long n);
		Rational(long long n, long long d);
		/* Governs all interactions between Rational numbers */

	private:
		/* Numerator and denominator can only be whole numbers */
		long long	_n;
		long long	_d;
};

// Irrational is left out in this case

class Complex : public Number {
	public:
		Complex(Real imag);
		Complex(Real real, Real imag);
	private:
		/* Form: a + bi where a and b are real
		Both real and imaginary part can be integral, float, fraction, root etc 
		imaginary part specifies coefficient of implicit i, where i^2 = -1 */
		Real	_real;
		Real	_imag;
};

class Radical : public Number {
	public:
		Radical();
	private:
		/* Multiplier can be any type of number, number under radix can be anything.
		If it is a non-negative real number, root is Real, otherwise it's Complex;
		*/
		Real	_mult;
		Number	_root;
};
