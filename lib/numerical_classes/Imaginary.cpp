#include "Imaginary.h"

Imaginary::Imaginary(Rational real, Rational imag):
_real{real}, _imag{imag} {}

Imaginary::Imaginary(const Imaginary& rhs) :
_real{rhs._real}, _imag{rhs._imag} {}

Imaginary	    &Imaginary::operator=(const Imaginary &rhs) {
    if (this != &rhs) {
        _real = rhs._real;
        _imag = rhs._imag;
    }
    return *this;
}

Imaginary::operator std::string() {
    // TODO: split on sign between real and imag?
    std::string res = "";
    if (_real == 0 && _imag == 0) {
        res += std::to_string(0);
    }
    else {
        if (_real != 0) {
            res += std::string(_real);
        }
        if (_imag != 0) {
            res += std::string(_imag) + "i";
        }
    }
    return res;
}

Imaginary			Imaginary::operator-() const {
    Imaginary tmp = *this;

    tmp._real = -tmp._real;
    tmp._imag = -tmp._imag;
    return tmp;
}

Rational          Imaginary::getRational(void)    const
{
    return (_real);
}

Rational          Imaginary::getImag(void)    const
{
    return (_imag);
}

void            Imaginary::setRational(Rational real)
{
    _real = real;
}

void            Imaginary::setImag(Rational imag)
{
    _imag = imag;
}

