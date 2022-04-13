#include "ParseToken.h"
#include <regex>

ParseToken::ParseToken(coeffTypes type, std::string coeff) {
	_degree = std::nullopt;
	_coeff = coeff;
	_type = type;
}

ParseToken::ParseToken(coeffTypes type, std::string coeff, std::string degree) {
	_degree = degree;
	_coeff = coeff;
	_type = type;
}

ParseToken::~ParseToken() {
	
}

bool		operator==(const ParseToken &lhs, const ParseToken &rhs) {
		return (lhs.getType() == rhs.getType()
		&& lhs.getCoeff() == rhs.getCoeff()
		&& ((!lhs.getDegree() && !rhs.getDegree()) ||
		lhs.getDegree().value() == rhs.getDegree().value()));
}

void		ParseToken::setDegree(std::string degree) {
	_degree = degree;
}

ParseToken::coeffTypes					ParseToken::getType() const {
	return (_type);
}

std::string					ParseToken::getCoeff() const {
	return (_coeff);
}

std::optional<std::string> 	ParseToken::getDegree() const {
	return (_degree);
}

void		ParseToken::print() {
	std::cout << "Type: ";
	if (_type == ParseToken::coeffTypes::decimal) {
		std::cout << "Decimal\n";
	}
	else if (_type == ParseToken::coeffTypes::integer) {
		std::cout << "Integer\n";
	}
	else if (_type == ParseToken::coeffTypes::rational) {
		std::cout << "Fraction\n";
	}
	if (_degree) {
		std::cout << "Degree: " << _degree.value() << "\n\n";
	}
	else {
		std::cout << "\n";
	}
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
	std::regex					first_match_rational{R"(^[+-]?\d+(\/{1}[+-]?\d+|\([+-]?\d+\/{1}[+-]?\d+\)))"};
	std::regex					first_match_int{R"(^[+-]?(\d+|[Xx]{1}))"};

	std::regex					non_first_match_decimal{R"(^[+-]{1}\d+\.{1}\d+)"};
	std::regex					non_first_match_rational{R"(^[+-]{1}\d+(\/{1}[+-]?\d+|\([+-]?\d+\/{1}[+-]?\d+\)))"};
	std::regex					non_first_match_int{R"(^[+-](\d+|[Xx]{1}))"};

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

ParseToken				getParsingToken(std::string &input, bool first) {
	try {
		auto [ type, token ] = getParseCoeffAndType(input, first);
		auto degree = getParseDegree(input);
		if (degree) {
			return ParseToken(type, token, degree.value());
		}
		else {
			return ParseToken(type, token);
		}
	}
	catch (std::invalid_argument &e) { throw e; }
}

std::vector<ParseToken>	parseHalf(std::string &half) {
	std::vector<ParseToken> tokens = {};
	bool first = true;
	while (!half.empty()) {
		try {
			ParseToken t = getParsingToken(half, first);
			first = false;
			tokens.push_back(t);
		}
		catch (std::invalid_argument &e) {
			throw e;
		}
	}
	return tokens;
}

std::pair<std::string, std::string>		getParsingHalves(std::string &eq) {
	std::regex 					match_halves{R"([=]+)"};
	std::sregex_token_iterator 	it{eq.begin(), eq.end(), match_halves, -1};
	std::vector<std::string> 	halves{it, {}};

	if (halves.size() != 2) {
		throw std::invalid_argument("Equation must contain exactly on '=' sign followed by at least one number.");
	}
	return	std::make_pair(halves.at(0), halves.at(1));
}

std::pair<std::vector<ParseToken>, std::vector<ParseToken>>	getParsingTokens(std::string &eq) {
	eq.erase(std::remove_if(eq.begin(), eq.end(), ::isspace),
	eq.end());
	std::cout << "String to parse: " << eq << "\n";
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
