#ifndef PARSE_TOKEN_H
#define PARSE_TOKEN_H
#include <string>
#include <optional>
#include <iostream>

class ParseToken {
	public:
		enum coeffTypes {
			rational, decimal, integer
		};
		ParseToken(coeffTypes type, std::string coeff);
		ParseToken(coeffTypes type, std::string coeff, std::string degree);
		~ParseToken();
		std::string					getCoeff() const;
		std::optional<std::string> 	getDegree() const;
		coeffTypes					getType() const;
		void		setDegree(std::string degree);
		void		print();
	private:
		std::string					_coeff;
		std::optional<std::string> 	_degree;
		coeffTypes					_type;
};

bool            operator==(const ParseToken &lhs, const ParseToken &rhs);
#endif
