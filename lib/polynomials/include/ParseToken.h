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
		void		setDegree(std::string degree);
		void		print();
	private:
		std::string					_coeff;
		std::optional<std::string> 	_degree;
		coeffTypes					_type;
};

#endif
