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

long long		string_to_ll(const char *str, size_t *index) {
	char 		*end;
	long long 	whole;
	whole = strtoll(&(str[*index]), &end, 10);
	if (end == &(str[*index])) { throw std::invalid_argument("Could not parse whole part of number."); }
	if (errno == ERANGE) { throw std::overflow_error("Whole part of number could not be represented as long long."); }
	*index += end - str;
	return whole;
}

void			factor_gcd(long long *num, long long *denum) {
	long long gcd = std::gcd(*num, *denum);
	if (gcd != 0) {
		*num /= gcd;
		*denum /= gcd;
	}
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

Rational		rational_string_to_rational(std::string &str, size_t *i) {
	// TODO: denominator CANNOT be 0
	size_t		start = *i;
	long long 	numerator, denominator;

	try {
		numerator = string_to_ll(str.c_str(), &start);
		++start;
		denominator = string_to_ll(str.c_str(), &start);
		if (denominator == 0) {
			throw std::invalid_argument("Denominator of fraction cannot be zero.");
		}
		*i = start;
		return Rational(numerator, denominator);
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

Rational		decimal_string_to_rational(std::string &str, size_t *i) {
	size_t		start = *i;
	long long 	whole, denominator, prev_read, numerator;

	try {
		whole = string_to_ll(str.c_str(), &start);
		if (str[start] == '.') { ++start; }
		prev_read = start;
		numerator = string_to_ll(str.c_str(), &start);
		denominator = get_base_ten(start - prev_read);
		/* Factor out gcd of numerator and denominator */
		factor_gcd(&numerator, &denominator);
		/* Combine whole part and numerator */
		combine_whole_numerator(&numerator, whole, denominator);
	}
	catch (std::overflow_error &e) {
		throw e;
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
	printf("rational: %lld/%lld\n", numerator, denominator);
	*i = start;
	return Rational(numerator, denominator);
}

long double	decimal_string_to_double(std::string &str, size_t *i) {
	char		*end;
	long double res = strtold(&(str[*i]), &end);

	if (end == &(str[*i])) { throw std::invalid_argument("Could not parse whole part of number."); }
	if (errno == ERANGE) { throw std::overflow_error("Whole part of number could not be represented as long long."); }
	*i += (end - str.c_str());
	printf("long double: %Lf\n", res);
	return res;
}

bool		is_decimal_string(std::string &str, size_t i) {
	size_t start = i;
	while (isdigit(str[i])) {
		i++;
	}
	return (str[i] == '.' && isdigit(str[i + 1]) && start != i);
}

bool		is_rational_string(std::string &str, size_t i) {
	/* Check whether form is n/m where n and m are whole numbers */
	size_t start = i;
	while (isdigit(str[i])) {
		i++;
	}
	/* Has to have at least one digit before '/' and at least one after, 
	possibly with +/- between */
	return (str[i] == '/' && (isdigit(str[i + 1]) || 
	((str[i + 1] == '+' || str[i + 1] == '-') && isdigit(str[i + 2])))
	&& start != i);
}

coeffOpts		get_coefficient(std::string &str, size_t *i) {
	// TODO: side for sign!!..
	// TODO: HAS TO start with sign?
	if (!(str[*i] == '-' || str[*i] == '+')) {
		throw std::invalid_argument("Invalid token in equation, expected '+' or '-'.");
	}
	else {
		++(*i);
	}
	if (is_rational_string(str, *i)) {
		printf("Is rational string.");
		try {
			Rational r = rational_string_to_rational(str, i);
			return r;
		}
		catch (std::overflow_error &e) {
			throw (e);
		}
		catch (std::invalid_argument &e) {
			throw (e);
		}
	}
	else if (is_decimal_string(str, *i))
	{
		printf("Is decimal string.");
		try {
			Rational r = decimal_string_to_rational(str, i);
			return r;
		}
		catch (...) {
			try {
				long double n = decimal_string_to_double(str, i);
				return n;
			}
			catch (std::overflow_error &e) {
				throw (e);
			}
			catch (std::invalid_argument &e) {
				throw (e);
			}
		}
	}
	else {
		try {
			long long n = string_to_ll(str.c_str(), i);
			return n;
		}
		catch (std::overflow_error &e) {
			throw (e);
		}
		catch (std::invalid_argument &e) {
			throw (e);
		}
	}
}

/* Make sure if strlen check is neccessary */
int		get_degree(std::string &str, size_t *i) {
	int degree = 0;
	if (str[*i] != '*') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (str[*i] != 'X') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (str[*i] != '^') {
		throw std::invalid_argument("Syntax error");
	}
	(*i)++;
	if (!isdigit(str[*i]) && !(str[*i] == '+')) {
		throw std::invalid_argument("Syntax error");
	}
	degree = atoi(&(str[*i]));
	if (str[*i] == '+') {
		(*i)++;
	}
	while (*i < str.length() && isdigit(str[*i])) {
		(*i)++;
	}
	return (degree);
}

/* Assumes format of a * x ^ p where a is a number, x a character in the al*/
void	parse_token(Equation *token_info, std::string &str, size_t *i) {
	printf("Parse token: %s\n", &(str[*i]));
	try {
		coeffOpts		coeff = get_coefficient(str, i);
		// TODO: safe get degree
		int				degree = get_degree(str, i);
		token_info->add(coeff, degree);
	}
	catch (std::invalid_argument &e) {
		throw (e);
	}
	catch (std::overflow_error &e) {
		throw (e);
	}
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

	std::smatch m;
	if (std::regex_search(str, m, dec)) {
		type = ParseToken::coeffTypes::decimal;
	}
	else if (std::regex_search(str, m, rat)) {
		type = ParseToken::coeffTypes::rational;
	}
	else if (std::regex_search(str, m, integ)) {
		type = ParseToken::coeffTypes::integer;
	}
	else { 
		throw std::invalid_argument("Could not parse coefficient, invalid form."); 
	}
	coeff = m[0];
	str.erase(0, m.length());
	return std::make_pair(type, coeff);
}

std::pair<ParseToken::coeffTypes, std::string>	getParseCoeffAndType(std::string &str, bool first) {
	std::regex					first_match_decimal{R"(^[+-]?\d+\.{1}\d+)"};
	std::regex					first_match_rational{R"(^[+-]?\d+\/{1}[+-]?\d+)"};
	std::regex					first_match_int{R"(^[+-]?\d+)"};

	std::regex					non_first_match_decimal{R"(^[+-]{1}\d+\.{1}\d+)"};
	std::regex					non_first_match_rational{R"(^[+-]{1}\d+\/{1}[+-]?\d+)"};
	std::regex					non_first_match_int{R"(^[+-]{1}\d+)"};

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

std::optional<std::string>	getParseDegree(std::string &str) {
	std::regex					degree_regex{R"(^\*?[Xx]{1}(\^\d+)?)"};

	std::smatch m;
	std::string degree;
	std::cout << "STRING LEFT BEFORE PARSE DEGREE: " << str << "\n\n"; 
	if (std::regex_search(str, m, degree_regex)) {
		degree = m[0];
		std::cout << m[0] << "\n" << m.length();
		std::cout << "STRING LEFT AFTER PARSE DEGREE: " << str << "\n\n"; 
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
		std::cout << "STRING LEFT\n" << half << "\n";
		try {
			std::pair<ParseToken::coeffTypes, std::string> tc = getParseCoeffAndType(half, first);
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
	std::cout << half;
	return tokens;
}

std::pair<std::vector<ParseToken>, std::vector<ParseToken>>	getParsingTokens(std::string &eq) {
	try {
		auto [left, right] = getParsingHalves(eq);
		std::vector<ParseToken> leftParse = parseHalf(left);
		std::vector<ParseToken> rightParse = parseHalf(right);
		for (std::vector<ParseToken>::iterator it = leftParse.begin(); it != leftParse.end(); ++it) {
			(*it).print();
		}
		for (std::vector<ParseToken>::iterator it = rightParse.begin(); it != rightParse.end(); ++it) {
			(*it).print();
		}
		return std::make_pair(leftParse, rightParse);
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

Equation	parse_equation(std::string &equation) {
	// Equation::operationSide side = Equation::operationSide::left;
	Equation token_info = Equation();
	equation.erase(std::remove_if(equation.begin(), equation.end(), ::isspace),
	equation.end());
	getParsingTokens(equation);

	// size_t i = 0;
	// while (i < equation.length())
	// {
	// 	try {
	// 		if (equation[i] == '=') {
	// 			if (token_info.getEquationLeft().empty()) {
	// 				throw std::invalid_argument("Starting with equals sign is illegal.");
	// 			}
	// 			if (token_info.getSide() != Equation::operationSide::left) {
	// 				throw std::invalid_argument("Only one equals sign allowed per equation.");
	// 			}
	// 			i++;
	// 			token_info.setSide(Equation::operationSide::right);
	// 		}
	// 		parse_token(&token_info, equation, &i);
	// 	}
	// 	catch (std::invalid_argument &e) {
	// 		throw;
	// 	}
	// 	catch (std::overflow_error &e) {
	// 		throw (e);
	// 	}
	// }
	// if (token_info.getSide() == Equation::operationSide::left) {
	// 	throw std::invalid_argument("No equals sign found, not a valid equation.");
	// }
	// token_info.print();
	// token_info.sort();
	// // TODO: Output what the equation looks like in reduced form
	// token_info.simplify();
	// // token_info.print();
	return token_info;
}
