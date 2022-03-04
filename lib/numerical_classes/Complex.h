#ifndef COMPLEX_H
# define COMPLEX_H
# include <iostream>

/* Holds complex number of form z = (x, iy) where x is the real part and y is the 
imaginary part */

/* Template this for ints as well? */
class ComplexNumber {
	private:
		double _real;
		double _imag;

	public:
		ComplexNumber(double real, double imag);
		~ComplexNumber(void);
		ComplexNumber(const ComplexNumber& other);
		double			getReal(void)	const;
		double			getImag(void)	const;
		void			setReal(double real);
		void			setImag(double imag);
		ComplexNumber&	operator=(const ComplexNumber& num);
		bool			operator==(const ComplexNumber& other)	const;
		bool			operator!=(const ComplexNumber& other)	const;
		ComplexNumber	operator*(const ComplexNumber& other)	const;
		ComplexNumber	operator*(double real_scalar)	const;
		ComplexNumber	operator*(int real_scalar)	const;
        // ComplexNumber	operator/(double scalar)  const;
		// ComplexNumber	operator/(int scalar)  const;
};

#endif
