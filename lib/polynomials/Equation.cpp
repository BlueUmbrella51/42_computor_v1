#include "Equation.h"

Equation::Equation() : _side(Equation::operationSide::left), _variable{'0'} {
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

Equation::operationSide	Equation::getSide() {
	return _side;
}

void	Equation::setSide(Equation::operationSide s) {
	_side = s;
}

int		Equation::getHighestDegree() {
	return _highest_degree;
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
				// add " - " to string
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
				if ((*it).getCoeff() < 0) { tmp.erase(0, 1); }
				if ((*it).getCoeff() < 0) {
					// add " - " to string
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

	try {
		tmp.setCoeff(-tmp.getCoeff());
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	_tokensLeft.push_back(tmp);
	_tokensRight.push_back(tmp);
	sortTokens(_tokensLeft);
	sortTokens(_tokensRight);
	combineTokensByDegree(_tokensLeft);
	combineTokensByDegree(_tokensRight);
	removeZeroCoeff(_tokensLeft);
	return *this;
}

Equation				&Equation::operator+=(const Token &t) {
	Token tmp = t;

	try {
		tmp.setCoeff(-tmp.getCoeff());
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	_tokensLeft.push_back(tmp);
	_tokensRight.push_back(tmp);
	sortTokens(_tokensLeft);
	sortTokens(_tokensRight);
	combineTokensByDegree(_tokensLeft);
	combineTokensByDegree(_tokensRight);
	removeZeroCoeff(_tokensLeft);
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
// Equation				&operator*=(const Token &t);

std::ostream		&operator<<(std::ostream &os, const Equation &eq) {
	auto s = std::string(eq);
	os << s;
	return os;
}

std::optional<Token>		Equation::findTokenOfDegree(std::list<Token> &tokens, int degree) {
	auto it = tokens.begin();
	while (it != tokens.end()) {
		if ((*it).getDegree() == degree) {
			return (*it);
		}
		++it;
	}
	return std::nullopt;
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

void	Equation::sortTokens(std::list<Token> &lst) {
	lst.sort([](const Token & t1, const Token & t2) {
		return (t1.getDegree() > t2.getDegree());
	});
}

void	Equation::combineTokensByDegree(std::list<Token> &lst) {
	/* Only works on SORTED list */
	std::list<Token>::iterator it = lst.begin();
	std::list<Token>::iterator curr = it;
	++it;
	while (it != lst.end()) {
		if ((*it).getDegree() == (*curr).getDegree()) {
			try {
				(*curr).setCoeff((*curr).getCoeff() + (*it).getCoeff());
				it = lst.erase(it);
			}
			catch (std::overflow_error &e) {
				throw e;
			}
		}
		else {
			curr = it;
			++it;
		}
	}
}

void	Equation::moveTokensLeft() {
	std::list	tmp(_tokensRight);
	std::list<Token>::iterator iter = tmp.begin();
	try {
		while (iter != tmp.end())
		{
			if ((*iter).getCoeff() <= 0) {
				*this += *iter;
			}
			else {
				*this -= *iter;
			}
			iter = _tokensRight.erase(iter);
		}
	}
	catch (std::overflow_error &e) { throw (e); }
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
	std::list<Token>::iterator it = _tokensLeft.begin();

	while (it != lst.end()) {
		if ((*it).getCoeff() == 0) {
			it = lst.erase(it);
		}
		else {
			++it;
		}
	}
	// TODO
	if (!_tokensLeft.empty())
		findHighestDegreeLeft();
}

void	Equation::factor(std::list<Token> &lst) {
	// There can never be less than two tokens so this should be safe
	// TODO: wrap in try/ catch
	// TODO: make gcd negative if first token is negative
	std::list<Token>::iterator 	it = lst.begin();
	Rational						gcd = (*it).getCoeff();

	++it;
	while (it != lst.end()) {
		auto curr = (*it).getCoeff();
		gcd = getGcd(curr, gcd);
		it++;
	}
	/* If first token in sorted equation is negative, factor out that -1 
	TODO: necessary? (done in simplify) */
	if ((*lst.begin()).getCoeff() < 0) {
		gcd = -gcd;
	}
	it = lst.begin();
	for (std::list<Token>::iterator i = lst.begin(); i != lst.end(); ++i) {
		try {
			(*i).setCoeff((*i).getCoeff() / gcd);
		}
		catch (std::overflow_error &e) { throw e; }
	}
}

void	Equation::simplify() {
	/* 	Moves all tokens to left of equation
		Combines any tokens of same degree
	 */
	try {
		combineTokensByDegree(_tokensRight);
		moveTokensLeft();
		sortTokens(_tokensLeft);
		combineTokensByDegree(_tokensLeft);
		removeZeroCoeff(_tokensLeft);
		/* If first token in sorted equation is negative, factor out that -1 */
		if (!_tokensLeft.empty() && (*_tokensLeft.begin()).getCoeff() < 0) {
			*this /= -1;
		}
	}
	catch (std::overflow_error &e) { throw e; }
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

	try {
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
		// factorGcd(numerator, denominator);
		return Fraction(whole, numerator, denominator);
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

Fraction		decimal_string_to_rational(std::string &str) {
	size_t		i = 0;
	size_t		prev = 0;
	long long 	whole, denominator, numerator;

	try {
		whole = string_to_ll(str, &i);
		/* skip '.' */
		++i;
		prev = i;
		numerator = string_to_ll(str, &i);
		if (str[0] == '-' && whole == 0) {
			numerator = -numerator;
		}
		denominator = int_pow(10, i - prev);
		/* Factor out gcd of numerator and denominator */
		factorGcd(numerator, denominator);
		/* Combine whole part and numerator */
		return Fraction(whole, numerator, denominator);
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
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
		try {
			Fraction r = rational_string_to_rational(str);
			return Rational(r);
		}
		catch (std::overflow_error &e) { throw e; }
		catch (std::invalid_argument &e) { throw e; }
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
			catch (std::invalid_argument &e) { throw e; }
		}
	}
	else {
		try {
			long long n = string_to_ll(str);
			return Rational(Fraction(n));
		}
		catch (std::overflow_error &e) { throw (e); }
		catch (std::invalid_argument &e) { throw e; }
	}
}

/* Make sure if strlen check is neccessary */
long int		get_degree(std::string &str) {
	std::string::iterator	it = str.begin();
	char					*end;

	while (it != str.end() && !isdigit(*it)) {
		++it;
	}
	/* If no digits are specified as power, we just assume ^1 was meant.
	This allows input like: 2X rather than 2X^0 */
	if (it == str.end()) {
		return 1;
	}
	std::string		s{ *it };
	long int		degree = strtol(s.c_str(), &end, 10);
	if (end == s.c_str()) { throw std::invalid_argument("Could not parse degree."); }
	if (errno == ERANGE) { throw std::overflow_error("Degreer could not be represented as long."); }
	return degree;
}

Token		parse_token(ParseToken &pt) {
	try {
		ParseToken::coeffTypes		type = pt.getType();
		std::string					coeff_str = pt.getCoeff();
		std::optional<std::string>	degree_str = pt.getDegree();
		Rational			 		coeff = get_coefficient(coeff_str, type);
		/* If no discriminant was given we assume one with power 0, which
		comes down to coefficient * 1. */
		long int					degree = 0;
		if (degree_str) {
			degree = get_degree(degree_str.value());
		}
		return Token(coeff, degree);
	}
	catch (std::invalid_argument &e) { throw (e); }
	catch (std::overflow_error &e) { throw (e); }
}

Equation		parse_equation(std::string &input) {
	Equation token_info = Equation();
	try {
		auto [left, right] = getParsingTokens(input);
		for (std::vector<ParseToken>::iterator it = left.begin(); it != left.end(); ++it) {
			token_info.add(parse_token(*it));
		}
		token_info.setSide(Equation::operationSide::right);
		for (std::vector<ParseToken>::iterator it = right.begin(); it != right.end(); ++it) {
			token_info.add(parse_token(*it));
		}
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	return token_info;
}
