
// case: x
// Token::Token() {
// 	_sign = '+';
// 	_coeff = 1.0f;
// 	_degree = 1;
// }

// case: -x or x
Token::Token(char sign) {
	_sign = sign;
	_coeff = 1.0f;
	_degree = 1;
}

// case: 2 or -2
Token::Token(float coeff, char sign) {
	_sign = sign;
	_coeff = coeff;
	_degree = 0;
}

// case: -2
// Token::Token(float coeff, char sign) {
// 	_sign = sign;
// 	_coeff = coeff;
// 	_degree = 0;
// }

// case: x^3 or -x^3
Token::Token(int degree, char sign) {
	_sign = sign;
	_coeff  = 1.0f;
	_degree = degree;
}

// case 2x or -2x
Token::Token(float coeff, int degree, )

// case: -x^3
// Token::Token(int degree, char sign) {
// 	_sign = sign;
// 	_coeff  = 1.0f;
// 	_degree = degree;
// }



// Token::Token(int degree, float coeff) {
// 	_degree = degree;
// 	_coeff = coeff;
// 	_sign = '+';
// }

// Token::Token(char var, char sign, float coeff, int degree) :
// 	_var(Variable(var, degree))
// {
// 	_sign = sign;
// 	_coeff = coeff;
// }

// Token::Token(float coeff, char sign) :
// 	_var(std::nullopt)
// {
// 	_sign = sign;
// 	_coeff = coeff;
// }
