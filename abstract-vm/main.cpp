#include "abstractvm.hpp"
#include "lexer.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	AbstractVM vm;
	Lexer lexer(argv[1]);

	try {
		Token token(Token::Type::INVALID, "");

		while ((token = lexer.nextToken()).getType() != Token::Type::INVALID) {
			std::cout << "Token type: " << token.getType() << " \"" << token.getLexeme() << "\"" << std::endl;
		}
	} catch (LexerException &e) {
		std::cerr << "Parser error: " << e.what() << std::endl;
	}

	return 0;
}
