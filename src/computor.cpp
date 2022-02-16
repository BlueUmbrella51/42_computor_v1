#include "../headers/computor.h"
#include "../headers/token.hpp"

int main(int argc, char *argv[]) {
	Token a = Token(-1, 0);
	Token b = Token(13, 8);
	Token c = Token(2, 4);
	// a.print();
	// b.print();
	// c.print();
	Tokens expression = Tokens('x');
	expression.add(a);
	expression.add(b);
	expression.add(c);
	// expression.print();
	expression.sort();
	expression.print();
	std::cout << std::endl;
	expression.combine();
	expression.print();
	std::cout << argv[1];
	std::cout << argc;
}
