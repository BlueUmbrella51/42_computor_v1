#include "headers/Complex.hpp"

ComplexNumber::ComplexNumber(double real, double imag):
_real(0),
_imag(0)
{
    _real = real;
    _imag = imag;
}

ComplexNumber::~ComplexNumber(void)
{
    
}

ComplexNumber::ComplexNumber(const ComplexNumber& other)
{
    _real = other.getReal();
    _imag = other.getImag();
}

double          ComplexNumber::getReal(void)    const
{
    return (_real);
}

double          ComplexNumber::getImag(void)    const
{
    return (_imag);
}

void            ComplexNumber::setReal(double real)
{
    _real = real;
}

void            ComplexNumber::setImag(double imag)
{
    _imag = imag;
}

ComplexNumber&  ComplexNumber::operator=(const ComplexNumber& other)
{
    if (this == &other)
		return (*this);
    setReal(other.getReal());
    setImag(other.getImag());
    return (*this);
}

bool            ComplexNumber::operator==(const ComplexNumber& other)   const
{
    return (_real == other.getReal() && _imag == other.getImag());
}

bool            ComplexNumber::operator!=(const ComplexNumber& other)   const
{
    return (_real != other.getReal() || _imag != other.getImag());
}

ComplexNumber   ComplexNumber::operator*(const ComplexNumber& other)    const
{
    /* Formula: (a + ib)(c + id) = (ac - bd) + i(ad + bc) */
    return ComplexNumber(
        (_real * other.getReal()) - (_imag * other.getImag()),
        (_real * other.getReal()) + (_imag * other.getReal()));
}

ComplexNumber   ComplexNumber::operator*(double real_scalar)    const
{
    return ComplexNumber(_real * real_scalar, _imag);
}

ComplexNumber   ComplexNumber::operator*(int real_scalar)   const
{
    return ComplexNumber(_real * static_cast<double>(real_scalar), _imag);
}

// ComplexNumber   ComplexNumber::operator/(int real_scalar)   const {

// }