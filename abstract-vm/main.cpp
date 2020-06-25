#include "abstractvm.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

std::string readInput(std::istream &stream)
{
	std::string input;
	std::string line;

	while (std::getline(stream, line) && line != ";;") {
		input += line;
		if (stream.good()) {
			input += "\n";
		}
	}
	return input;
}

int main(int argc, char **argv)
{
	AbstractVM vm;
	std::string input;
	std::string line;

	if (argc > 2) {
		std::cerr << "usage: " << argv[0] << " [file]" << std::endl;
		return EXIT_FAILURE;
	} else if (argc < 2) {
		input = readInput(std::cin);
	} else {
		std::ifstream file(argv[1]);

		if (!file.is_open()) {
			std::cerr << "Unable to open file " << argv[1] << std::endl;
			return EXIT_FAILURE;
		}
		input = readInput(file);
	}
	Lexer lexer(input);
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
	return EXIT_SUCCESS;
}
