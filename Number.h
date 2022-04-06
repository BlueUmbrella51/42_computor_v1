#include <type_traits>

class Fraction;
class Complex;

class Number {
	/* Governs interactions between Rational and Complex numbers */
	public:
};

Number	operator*(const Fraction &r, const Complex &c);
Number	operator*(const Complex &c, const Fraction &r);
Number	operator/(const Fraction &r, const Complex &c);
Number	operator/(const Complex &c, const Fraction &r);
Number	operator+(const Fraction &r, const Complex &c);
Number	operator+(const Complex &c, const Fraction &r);
Number	operator-(const Fraction &r, const Complex &c);
Number	operator-(const Complex &c, Fraction &r);

class Rational: Number  {
	/* Includes all Fraction numbers and all Irrational number, governs interaction
	between Fractions and decimals / integrals (if not expressed as rationals) */
	// public:
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			multiply(Fraction &r, T n) {
	// 		return (long double(r) * n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			multiply(T n, Fraction &r) {
	// 		return 	multiply(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			divide(Fraction &r, T n) {
	// 		return (long double(r) / n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			divide(T n, Fraction &r) {
	// 		return divide(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			add(Fraction &r, T n) {
	// 		return (long double(r) + n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			add(T n, Fraction &r) {
	// 		return add(r, n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			subtract(Fraction &r, T n) {
	// 		return (long double(r) + n);
	// 	}
	// 	template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
	// 	long double			subtract(T n, Fraction &r) {
	// 		return subtract(r, n);
	// 	}
};

class Fraction : public Rational {
	/* Represents all Fraction numbers such as integrals and fractions
	that can be expressed a ratio between two integrals (i.e. -4/8, 4/1) */
	public:
		Fraction(long long n);
		Fraction(long long n, long long d);
		/* Governs all interactions between Fraction numbers */

	private:
		/* Numerator and denominator can only be whole numbers */
		long long	_n;
		long long	_d;
};

// Irrational is left out in this case

class Complex : public Number {
	public:
		Complex(Rational imag);
		Complex(Rational real, Rational imag);
	private:
		/* Form: a + bi where a and b are real
		Both real and imaginary part can be integral, float, fraction, root etc 
		imaginary part specifies coefficient of implicit i, where i^2 = -1 */
		Rational	_real;
		Rational	_imag;
};

class Radical : public Number {
	public:
		Radical();
	private:
		/* Multiplier can be any type of number, number under radix can be anything.
		If it is a non-negative real number, root is Rational, otherwise it's Complex;
		*/
		Rational	_mult;
		Number	_root;
};
