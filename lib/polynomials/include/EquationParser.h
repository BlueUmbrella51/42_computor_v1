// #ifndef EQUATION_PARSER_H
// #define EQUATION_PARSER_H
// #include "ParseToken.h"
// #include <vector>
// #include <regex>

// class EquationParser {
// 	private:
// 		std::regex 					match_halves{R"([=]+)"};
		
// 		std::regex					first_match_decimal{R"(^[+-]?\d+\.{1}\d+)"};
// 		std::regex					first_match_rational{R"(^[+-]?\d+\/{1}[+-]?\d+)"};
// 		std::regex					first_match_int{R"(^[+-]?\d+)"};

// 		std::regex					non_first_match_decimal{R"(^[+-]{1}\d+\.{1}\d+)"};
// 		std::regex					non_first_match_rational{R"(^[+-]{1}\d+\/{1}[+-]?\d+)"};
// 		std::regex					non_first_match_int{R"(^[+-]{1}\d+)"};

// 		std::regex					power_degree_regex{R"(^\*?[xX]{1}\^{1}0*[1-9]+\d*)"};
// 		std::regex					non_power_degree_regex{R"(^\*?[xX]{1}\^{1})"};
// 		std::string					_input;
// 		std::vector<ParseToken>		_leftEq;
// 		std::vector<ParseToken> 	_rightEq;
	
// 	public:
// 		EquationParser(std::string input);
// 		<Token>		parse();
// };

// #endif