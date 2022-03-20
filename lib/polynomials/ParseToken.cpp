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
		std::cout << "Rational\n";
	}
	std::cout << "Coeff: " << _coeff << "\n";
	if (_degree) {
		std::cout << "Degree: " << _degree.value() << "\n\n";
	}
	else {
		std::cout << "\n";
	}
}