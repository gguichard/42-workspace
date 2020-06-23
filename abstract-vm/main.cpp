#include "abstractvm.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	AbstractVM vm;
	Lexer lexer(argv[1]);
	Parser parser(lexer);

	try {
		parser.parseInput();
	} catch (LexerException &e) {
		std::cerr << "Lexer error: " << e.what() << std::endl;
	} catch (ParserException &e) {
		std::cerr << "Parser error: " << e.what() << std::endl;
	}
	return 0;
}
