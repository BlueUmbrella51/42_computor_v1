#include "Equation.h"

Equation::Equation() : _constType(ConstantType::constant), _side(Equation::operationSide::left) {
	_highest_degree = -1;
	_tokensLeft = {};
	_tokensRight = {};
}

std::list<Token>	&Equation::getEquationLeft() {
	return _tokensLeft;
}

std::list<Token>	&Equation::getEquationRight() {
	return _tokensRight;
}

Equation::operationSide	Equation::getSide() const {
	return _side;
}

void	Equation::setSide(Equation::operationSide s) {
	_side = s;
}

void	Equation::setConstType(Equation::ConstantType t) {
	_constType = t;
}

int		Equation::getHighestDegree() const {
	return _highest_degree;
}

bool	Equation::hasZeroDegreeTokens() const { 
	return _constType == ConstantType::zero_degree; 
}

Equation::operator std::string() const {
	std::string res = "";
	if (_tokensLeft.empty()) {
		res += "0";
	}
	for (auto it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
		std::string tmp = std::string(*it);
		if (it != _tokensLeft.begin()) {
			if ((*it).getCoeff() < 0) { tmp.erase(0, 1); }
			if ((*it).getCoeff() < 0) {
				res += " - " + tmp;
			}
			else {
				res += " + " + tmp;
			}
		}
		else { res += tmp; }
	}
	res += " = ";
	if (!_tokensRight.empty()) {
		for (auto it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
			std::string tmp = std::string(*it);
			if (it != _tokensRight.begin()) {
				if ((*it).getCoeff() < 0) { 
					tmp.erase(0, 1);
					res += " - " + tmp;
				}
				else {
					res += " + " + tmp;
				}
			}
			else { res += tmp; }
		}
	}
	else {
		res += "0";
	}
	return res;
}

Equation				&Equation::operator-=(const Token &t) {
	Token tmp = t;

	tmp.setCoeff(-tmp.getCoeff());
	_tokensLeft.push_back(tmp);
	_tokensRight.push_back(tmp);
	sortTokens(_tokensLeft);
	sortTokens(_tokensRight);
	combineTokensByDegree(_tokensLeft);
	removeZeroCoeff(_tokensLeft);
	combineTokensByDegree(_tokensRight);
	removeZeroCoeff(_tokensRight);
	return *this;
}

Equation				&Equation::operator+=(const Token &t) {
	Token tmp = t;

	tmp.setCoeff(-tmp.getCoeff());
	_tokensLeft.push_back(tmp);
	_tokensRight.push_back(tmp);
	sortTokens(_tokensLeft);
	sortTokens(_tokensRight);
	combineTokensByDegree(_tokensLeft);
	removeZeroCoeff(_tokensLeft);
	combineTokensByDegree(_tokensRight);
	removeZeroCoeff(_tokensRight);
	return *this;
}

Equation				&Equation::operator/=(const Token &t) {
	for (auto it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
		(*it).setCoeff((*it).getCoeff() / t.getCoeff());
	}
	for (auto it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
		(*it).setCoeff((*it).getCoeff() / t.getCoeff());
	}
	return *this;
}

Equation				&Equation::toNumerical() {
	for (auto it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
		(*it).setCoeff((long double)(*it).getCoeff());
	}
	for (auto it = _tokensRight.begin(); it != _tokensRight.end(); ++it) {
		(*it).setCoeff((long double)(*it).getCoeff());
	}
	return *this;
}

std::ostream		&operator<<(std::ostream &os, const Equation &eq) {
	auto s = std::string(eq);
	os << s;
	return os;
}

std::optional<Token>		Equation::findTokenOfDegree(std::list<Token> &tokens, int degree) const {
	auto it = tokens.begin();
	while (it != tokens.end()) {
		if ((*it).getDegree() == degree) {
			return (*it);
		}
		++it;
	}
	return std::nullopt;
}

Rational					Equation::findCoeffOfDegree(std::list<Token> &tokens, int degree) const {
	auto token = findTokenOfDegree(tokens, degree);

	if (token) {
		return Rational(token.value().getCoeff());
	}
	return 0;
}

void	Equation::add(Token token) {
	if (token.getDegree() > _highest_degree) {
		_highest_degree = token.getDegree();
	}
	if (_side == operationSide::left) {
		_tokensLeft.push_back(token);
	}
	else {
		_tokensRight.push_back(token);
	}
}

void	Equation::sortTokens(std::list<Token> &lst, int direction) {
	if (direction == 1) {
		lst.sort([](const Token & t1, const Token & t2) {
			/* Sort by degree, if same degree, constants comes first */
			return ((t1.getDegree() > t2.getDegree()) ||
			((t1.getDegree() == t2.getDegree()) && (t1.isConstant() == true)));
		});
	}
	else if (direction == -1) {
		lst.sort([](const Token & t1, const Token & t2) {
			/* Sort by degree, if same degree, constants comes after */
			return ((t1.getDegree() < t2.getDegree())
			|| ((t1.getDegree() == t2.getDegree()) && (t1.isConstant() == false)));
		});
	}
	else {
		std::cerr << "Invalid sorting direction provided, cannot sort tokens.\n";
	}
}

void	Equation::combineTokensByDegree(std::list<Token> &lst) {
	/* Only works on SORTED list */
	std::list<Token>::iterator it = lst.begin();
	std::list<Token>::iterator curr = it;
	++it;
	while (it != lst.end()) {
		if ((*it).getDegree() == (*curr).getDegree()) {
			(*curr).setCoeff((*curr).getCoeff() + (*it).getCoeff());
			it = lst.erase(it);
		}
		else {
			curr = it;
			++it;
		}
	}
}

void	Equation::moveTokensLeft() {
	while (!_tokensRight.empty()) {
		std::list<Token>::iterator iter = _tokensRight.begin();
		if ((*iter).getCoeff() <= 0) {
			*this += *iter;
		}
		else {
			*this -= *iter;
		}
	}
}

void		Equation::findHighestDegreeLeft() {
	_highest_degree = 0;
	for (std::list<Token>::iterator it = _tokensLeft.begin(); it != _tokensLeft.end(); ++it) {
		if ((*it).getDegree() > _highest_degree) {
			_highest_degree = (*it).getDegree();
		}
	}
}

void	Equation::removeZeroCoeff(std::list<Token> &lst) {
	std::list<Token>::iterator it = lst.begin();

	while (it != lst.end()) {
		if ((*it).getCoeff() == 0) {
			it = lst.erase(it);
		}
		else {
			++it;
		}
	}
}

void	Equation::factor(std::list<Token> &lst) {
	std::list<Token>::iterator 	it = lst.begin();
	Rational					gcd = (*it).getCoeff();

	++it;
	while (it != lst.end()) {
		auto curr = (*it).getCoeff();
		gcd = getGcd(curr, gcd);
		it++;
	}
	/* If first token in sorted equation is negative, factor out that -1 */
	if ((*lst.begin()).getCoeff() < 0) {
		gcd = -gcd;
	}
	it = lst.begin();
	for (std::list<Token>::iterator i = lst.begin(); i != lst.end(); ++i) {
		(*i).setCoeff((*i).getCoeff() / gcd);
	}
}

void	Equation::reduce() {
	sortTokens(_tokensRight, -1);
	combineTokensByDegree(_tokensRight);
	moveTokensLeft();
	sortTokens(_tokensLeft, -1);
	combineTokensByDegree(_tokensLeft);
	removeZeroCoeff(_tokensLeft);
	findHighestDegreeLeft();
	if (!_tokensLeft.empty() && (*_tokensLeft.begin()).getCoeff() < 0) {
		*this /= -1;
	}
}

void	Equation::simplify() {
	/* 	Moves all tokens to left of equation
		Combines any tokens of same degree
	 */
	sortTokens(_tokensRight);
	combineTokensByDegree(_tokensRight);
	moveTokensLeft();
	sortTokens(_tokensLeft);
	combineTokensByDegree(_tokensLeft);
	removeZeroCoeff(_tokensLeft);
	findHighestDegreeLeft();
	/* If first token in sorted equation is negative, factor out that -1 */
	if (!_tokensLeft.empty() && (*_tokensLeft.begin()).getCoeff() < 0) {
		*this /= -1;
	}
}

long long		string_to_ll(std::string &str, size_t *i) {
	char 					*end;
	long long 				whole;

	whole = strtoll(&(str[*i]), &end, 10);
	if (end == str.c_str()) { throw std::invalid_argument("Could not parse whole part of number."); }
	if (errno == ERANGE) { throw std::overflow_error("Whole part of number could not be represented as long long."); }
	*i = end - str.c_str();
	return whole;
}

long long		string_to_ll(std::string &str) {
	char 					*end;
	long long 				whole;

	whole = strtoll(str.c_str(), &end, 10);
	if (end == str.c_str()) { throw std::invalid_argument("Could not parse whole part of number."); }
	if (errno == ERANGE) { throw std::overflow_error("Whole part of number could not be represented as long long."); }
	return whole;
}

Fraction		rational_string_to_rational(std::string &str) {
	long long 		numerator, denominator, whole;
	size_t			i = 0;

	if (str.find('(') != std::string::npos) {
		whole = string_to_ll(str, &i);
		++i; // skip '('
	}
	else { whole = 0; }
	numerator = string_to_ll(str, &i);
	++i; // skip '/'
	denominator = string_to_ll(str, &i);
	if (denominator == 0) {
		throw std::invalid_argument("Denominator of fraction cannot be zero.");
	}
	return Fraction(whole, numerator, denominator);
}

Fraction		decimal_string_to_rational(std::string &str) {
	size_t		i = 0;
	size_t		prev = 0;
	long long 	whole, denominator, numerator;

	whole = string_to_ll(str, &i);
	/* skip '.' */
	++i;
	prev = i;
	numerator = string_to_ll(str, &i);
	if (str[0] == '-' && whole == 0) {
		numerator = -numerator;
	}
	denominator = intPow(10, i - prev);
	/* Combine whole part and numerator */
	return Fraction(whole, numerator, denominator);
}

long double	decimal_string_to_double(std::string &str) {
	char		*end;
	long double res = strtold(str.c_str(), &end);

	if (end == str.c_str()) { throw std::invalid_argument("Could not parse whole part of number."); }
	if (errno == ERANGE) { throw std::overflow_error("Number could not be represented as long double."); }
	return res;
}

Rational		get_coefficient(std::string &str, ParseToken::coeffTypes type) {
	if (type == ParseToken::coeffTypes::rational) {
		Fraction r = rational_string_to_rational(str);
		return Rational(r);
	}
	else if (type == ParseToken::coeffTypes::decimal) {
		try {
			Fraction r = decimal_string_to_rational(str);
			return Rational(r);
		}
		catch (std::overflow_error &e) {
			try {
				long double n = decimal_string_to_double(str);
				return Rational(n);
			}
			catch (std::overflow_error &e) { throw e; }
		}
	}
	else {
		long long n = string_to_ll(str);
		return Rational(Fraction(n));
	}
}

/* Make sure if strlen check is neccessary */
long int		get_degree(std::string &str) {
	std::string::iterator	it = str.begin();
	char					*end;

	while (it != str.end() && !isdigit(*it)) {
		/* Skips X^ */
		++it;
	}
	/* If no digits are specified as power, we just assume ^1 was meant.
	This allows input like: 2X rather than 2X^0 */
	if (it == str.end()) {
		return 1;
	}
	std::string 	s = std::string(it, str.end());
	long int		degree = strtol(s.c_str(), &end, 10);

	if (end == s.c_str()) { throw std::invalid_argument("Could not parse degree."); }
	if (errno == ERANGE) { throw std::overflow_error("Degree could not be represented as long."); }
	return degree;
}

Token			doParseToken(ParseToken &pt) {
	ParseToken::coeffTypes		type = pt.getType();
	std::string					coeff_str = pt.getCoeff();
	std::optional<std::string>	degree_str = pt.getDegree();
	Rational			 		coeff = get_coefficient(coeff_str, type);
	/* If no discriminant was given we assume one with power 0, which
	comes down to coefficient * 1. */
	bool	isConstant = (degree_str == std::nullopt) ? true: false;
	long	degree = 0;
	if (degree_str) {
		degree = get_degree(degree_str.value());
	}
	return Token(coeff, degree, isConstant);
}

Equation		doParseEquation(std::string &input) {
	Equation token_info = Equation();
	auto [left, right] = getParsingTokens(input);
	bool	constType = false;
	bool	zeroDegreeType = false;
	Token	tmp;
	for (std::vector<ParseToken>::iterator it = left.begin(); it != left.end(); ++it) {
		tmp = doParseToken(*it);
		if (tmp.getDegree() == 0) {
			if (tmp.isConstant()) { constType = true; }
			else { zeroDegreeType = true; }
		}
		token_info.add(tmp);
	}
	token_info.setSide(Equation::operationSide::right);
	for (std::vector<ParseToken>::iterator it = right.begin(); it != right.end(); ++it) {
		tmp = doParseToken(*it);
		if (tmp.getDegree() == 0) {
			if (tmp.isConstant()) { constType = true; }
			else { zeroDegreeType = true; }
		}
		token_info.add(tmp);
	}
	if (constType) {
		token_info.setConstType(Equation::ConstantType::constant);
	}
	else {
		token_info.setConstType(Equation::ConstantType::zero_degree);
	}
	if (constType && zeroDegreeType) {
		throw std::invalid_argument("Cannot mix constants (aka '7') with variable with degree zero type (aka '7 * x^0' / '7x^0).");
	}
	return token_info;
}
