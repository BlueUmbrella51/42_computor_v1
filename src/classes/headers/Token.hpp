#ifndef TOKEN_HPP
# define TOKEN_HPP
#include <stdio.h>
#include <iostream>

class Token
{
	private:
		double	_coeff;
		int		_degree;

	public:
		Token(float coeff, int degree);
		~Token();
		void	print();
		int		getDegree() const;
		double	getCoeff()	const;
		void	setCoeff(double c);
};

#endif
