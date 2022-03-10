#include "ParseToken.h"

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

void		ParseToken::setDegree(std::string degree) {
	_degree = degree;
}

void		ParseToken::print() {
	std::cout << "Type: " << _type << "\nCoeff: " << _coeff << "\n";
	if (_degree) {
		std::cout << "Degree: " << _degree.value() << "\n\n";
	}
	else {
		std::cout << "\n";
	}
}