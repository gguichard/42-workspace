#include "abstractvm.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <queue>
#include <iostream>

int main(int argc, char **argv)
{
	AbstractVM vm;
	Lexer lexer(argv[1]);
	Parser parser(lexer);

	try {
		std::queue<Token> tokens = parser.parseInput();

		vm.run(tokens);
	} catch (LexerException &e) {
		std::cerr << "Lexer error: " << e.what() << std::endl;
	} catch (ParserException &e) {
		std::cerr << "Parser error: " << e.what() << std::endl;
	} catch (VMException &e) {
		std::cerr << "VM error: " << e.what() << std::endl;
	}
	return 0;
}
