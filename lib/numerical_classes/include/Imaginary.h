#ifndef COMPLEX_H
# define COMPLEX_H
#include <iostream>
#include "Rational.h"
/* Holds complex number of form z = (x, iy) where x is the real part and y is the 
imaginary part */

/* Template this for ints as well? */
class Imaginary {
	private:
		Rational _real;
		Rational _imag;

	public:
		Imaginary(Rational real, Rational imag);
		Imaginary(const Imaginary& other);
		~Imaginary() = default;
		Imaginary	    	&operator=(const Imaginary &rhs);
		Rational		getRational(void)	const;
		Rational		getImag(void)	const;
		void			setRational(Rational real);
		void			setImag(Rational imag);

		operator		std::string ();
		Imaginary			operator-() const;
};

#endif
