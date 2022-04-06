#ifndef RADICAL_H
#define RADICAL_H
#include "Rational.h"
#include <variant>
#include <optional>

class	Radical {
	public:
		Radical(Rational discriminant, int degree);
		~Radical() = default;
		bool	hasSignificantRadicant() const;
		bool	hasFloatingPointRadicant() const;
		enum Type {
			real,
			imaginary
		};
		enum arithmeticType {
			floating,
			integral,
			fraction
		};
	private:
		Rational				_whole;	// can only be decimal OR floating point
		Rational				_radical; // Can be either 
		int						_degree;
		Type					_type;
		arithmeticType			_radicalType;
		std::optional<Rational>	_solution;
		std::optional<Rational>	getSolution();
	
	friend std::ostream    		&operator<<(std::ostream &os, const Radical &x);
};


#endif
