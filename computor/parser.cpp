#include "computor.h"

bool			all_digits_zero(std::string str) {
	size_t	i = 0;

	while (isdigit(str[i]) && str[i] == '0') {
		i++;
	}
	return (!isdigit(str[i]));
}

long long		get_base_ten(size_t	digits_read) {
	std::optional<long long> bt = pow_overflow<long long>(10, digits_read);
	if (!bt) { throw std::overflow_error("Could not represent base 10 value large enough to represent Rational."); }
	return (bt.value());
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

void			combine_whole_numerator(long long *num, long long whole, long long denom) {
	long long prev = whole;

	whole *= denom;
	if (whole / denom != prev) {
		throw std::overflow_error("Could not combine numerator and whole part.");
	}
	prev = *num;
	*num += whole;
	if (*num - whole != prev) {
		throw std::overflow_error("Could not combine numerator and whole part.");
	}
}

Rational		rational_string_to_rational(std::string &str) {
	long long 		numerator, denominator;
	size_t			i = 0;

	try {
		numerator = string_to_ll(str, &i);
		++i;
		denominator = string_to_ll(str, &i);
		if (denominator == 0) {
			throw std::invalid_argument("Denominator of fraction cannot be zero.");
		}
		ll_factor_gcd(&numerator, &denominator);
		return Rational(numerator, denominator);
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

Rational		decimal_string_to_rational(std::string &str) {
	size_t		i = 0;
	size_t		prev = 0;
	long long 	whole, denominator, numerator;

	try {
		whole = string_to_ll(str, &i);
		/* skip '.' */
		++i;
		prev = i;
		numerator = string_to_ll(str, &i);
		denominator = get_base_ten(i - prev);
		/* Factor out gcd of numerator and denominator */
		ll_factor_gcd(&numerator, &denominator);
		/* Combine whole part and numerator */
		combine_whole_numerator(&numerator, whole, denominator);
		return Rational(numerator, denominator);
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
	if (errno == ERANGE) { throw std::overflow_error("Whole part of number could not be represented as long double."); }
	return res;
}

Token::coeffOpts		get_coefficient(std::string &str, ParseToken::coeffTypes type) {
	if (type == ParseToken::coeffTypes::rational) {
		try {
			Rational r = rational_string_to_rational(str);
			return r;
		}
		catch (std::overflow_error &e) { throw e; }
		catch (std::invalid_argument &e) { throw e; }
	}
	else if (type == ParseToken::coeffTypes::decimal) {
		try {
			Rational r = decimal_string_to_rational(str);
			return r;
		}
		catch (std::overflow_error &e) {
			try {
				long double n = decimal_string_to_double(str);
				return n;
			}
			catch (std::overflow_error &e) { throw e; }
			catch (std::invalid_argument &e) { throw e; }
		}
	}
	else {
		try {
			long long n = string_to_ll(str);
			return n;
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

/* Assumes format of a * x ^ p where a is a number, x a character in the al*/
void	parse_token(Equation &token_info, ParseToken &pt) {
	try {
		ParseToken::coeffTypes		type = pt.getType();
		std::string					coeff_str = pt.getCoeff();
		std::optional<std::string>	degree_str = pt.getDegree();

		Token::coeffOpts 			coeff = get_coefficient(coeff_str, type);
		/* If no discriminant was given we assume one with power 0, which
		comes down to coefficient * 1. */
		long int					degree = 0;
		if (degree_str) {
			degree = get_degree(degree_str.value());
		}
		token_info.add(coeff, degree);
	}
	catch (std::invalid_argument &e) { throw (e); }
	catch (std::overflow_error &e) { throw (e); }
}

std::pair<std::string, std::string>		getParsingHalves(std::string &eq) {
	std::regex 					match_halves{R"([=]+)"};
	std::sregex_token_iterator 	it{eq.begin(), eq.end(), match_halves, -1};
	std::vector<std::string> 	halves{it, {}};

	if (halves.size() != 2) {
		throw std::invalid_argument("Only one '=' sign allowed in equation.");
	}
	return	std::make_pair(halves.at(0), halves.at(1));
}

std::pair<ParseToken::coeffTypes, std::string> getParseCoeffAndTypeInner(std::string &str,
std::regex dec, std::regex rat, std::regex integ) {
	ParseToken::coeffTypes	type;
	std::string				coeff;
	std::regex				only_x{R"(^[+-]?[Xx]{1})"};
	int						len_mod = 0;

	std::smatch m;
	if (std::regex_search(str, m, dec)) {
		type = ParseToken::coeffTypes::decimal;
		coeff = m[0];
	}
	else if (std::regex_search(str, m, rat)) {
		type = ParseToken::coeffTypes::rational;
		coeff = m[0];
	}
	else if (std::regex_search(str, m, integ)) {
		type = ParseToken::coeffTypes::integer;
		std::smatch tmp;
		if (std::regex_search(str, tmp, only_x)) {
			/* if only optional +/- and then X or x, we just replace the x with 1.
			we still need the X to parse the degree though, so we leave the
			X in the source string (len_mod). This is so we can infer -1x and 1x
			from -x and x. */
			coeff = tmp[0];
			std::replace(coeff.begin(), coeff.end(), 'X', '1');
			std::replace(coeff.begin(), coeff.end(), 'x', '1');
			len_mod = 1;
		}
		else {
			coeff = m[0];
		}
	}
	else { 
		throw std::invalid_argument("Could not parse coefficient, invalid form: " + str); 
	}
	str.erase(0, coeff.length() - len_mod);
	return std::make_pair(type, coeff);
}

std::pair<ParseToken::coeffTypes, std::string>	getParseCoeffAndType(std::string &str, bool first) {
	std::regex					first_match_decimal{R"(^[+-]?\d+\.{1}\d+)"};
	std::regex					first_match_rational{R"(^[+-]?\d+\/{1}[+-]?\d+)"};
	std::regex					first_match_int{R"(^[+-]?(\d+|[Xx]{1}))"};

	std::regex					non_first_match_decimal{R"(^[+-]{1}\d+\.{1}\d+)"};
	std::regex					non_first_match_rational{R"(^[+-]{1}\d+\/{1}[+-]?\d+)"};
	std::regex					non_first_match_int{R"(^[+-](\d+|[Xx]{1}))"};

	printf("STRING TO PARSE AS COEFF/TYPE\n");
	std::cout << str << "\n";
	if (first) {
		try {
			return getParseCoeffAndTypeInner(str, first_match_decimal, 
			first_match_rational, first_match_int);
		}
		catch (std::invalid_argument &e) { throw e; }
	}
	else {
		try {
			return getParseCoeffAndTypeInner(str, non_first_match_decimal, 
			non_first_match_rational, non_first_match_int);
		}
		catch (std::invalid_argument &e) { throw e; }
	}
}

std::optional<std::string>		getParseDegree(std::string &str) {
	std::regex					degree_regex{R"(^\*?[Xx]{1}(\^\+?\d+)?)"};

	std::smatch m;
	std::string degree;
	if (std::regex_search(str, m, degree_regex)) {
		degree = m[0];
		str.erase(0, m.length());
		return degree;
	}
	else {
		return std::nullopt;
	}
}

std::vector<ParseToken>	parseHalf(std::string &half) {

	std::vector<ParseToken> tokens = {};
	bool first = true;
	while (!half.empty()) {
		try {
			std::pair<ParseToken::coeffTypes, std::string> tc = getParseCoeffAndType(half, first);
			first = false;
			auto degree = getParseDegree(half);
			if (degree)
				tokens.push_back(ParseToken(tc.first, tc.second, degree.value()));
			else
				tokens.push_back(ParseToken(tc.first, tc.second));
		}
		catch (std::invalid_argument &e) {
			throw e;
		}
	}
	return tokens;
}

std::pair<std::vector<ParseToken>, std::vector<ParseToken>>	getParsingTokens(std::string &eq) {
	try {
		auto [left, right] = getParsingHalves(eq);
		std::vector<ParseToken> leftParse = parseHalf(left);
		std::vector<ParseToken> rightParse = parseHalf(right);
		return std::make_pair(leftParse, rightParse);
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

Equation	parse_equation(std::string &input) {
	// Equation::operationSide side = Equation::operationSide::left;
	Equation token_info = Equation();
	input.erase(std::remove_if(input.begin(), input.end(), ::isspace),
	input.end());
	try {
		auto [left, right] = getParsingTokens(input);
		std::cout << "LEFT SIDE:\n";
		for (std::vector<ParseToken>::iterator it = left.begin(); it != left.end(); ++it) {
			parse_token(token_info, *it);
		}
		token_info.setSide(Equation::operationSide::right);
		std::cout << "RIGHT SIDE:\n";
		for (std::vector<ParseToken>::iterator it = right.begin(); it != right.end(); ++it) {
			parse_token(token_info, *it);
		}
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	printf("AFTER PARSE TOKENS\n");
	token_info.print();
	return token_info;
}
