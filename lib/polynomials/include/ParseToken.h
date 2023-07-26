#ifndef PARSE_TOKEN_H
#define PARSE_TOKEN_H
#include <string>
#include <iostream>
#include <vector>

class ParseToken {
	public:
		enum coeffTypes {
			rational, decimal, integer
		};
		ParseToken(coeffTypes type, std::string coeff);
		ParseToken(coeffTypes type, std::string coeff, std::string degree);
		~ParseToken();
		std::string					getCoeff() const;
		std::string 				getDegree() const;
		coeffTypes					getType() const;
		void		setDegree(std::string degree);
		void		print();
	private:
		std::string					_coeff;
		std::string 				_degree;
		coeffTypes					_type;
};

bool            											operator==(const ParseToken &lhs, const ParseToken &rhs);
ParseToken													getParsingToken(std::string &input, bool first);
std::pair<std::vector<ParseToken>, std::vector<ParseToken>>	getParsingTokens(std::string &input);

#endif
