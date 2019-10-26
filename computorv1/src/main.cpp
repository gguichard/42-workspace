#include <memory>
#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include "lexer.hpp"
#include "parser.hpp"
#include "exprformula.hpp"
#include "solver.hpp"

static int parseOptions(int argc, char **argv)
{
	int options = 0;
	int opt;

	while ((opt = getopt(argc, argv, "d")) != -1)
	{
		switch (opt)
		{
		case 'd':
			options |= 0x1;
			break;
		default:
			return -1;
		}
	}
	return options;
}

int main(int argc, char **argv)
{
	int options = parseOptions(argc, argv);

	if (options == -1 || optind >= argc)
		std::cerr << "usage: " << argv[0] << " [-d] poly" << std::endl;
	else
	{
		Solver solver(argv[optind]);
		try
		{
			solver.solve(options & 0x1);
			return EXIT_SUCCESS;
		}
		catch (ParserException &e)
		{
			solver.parser().printError(e);
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << "." << std::endl;
		}
	}
	return EXIT_FAILURE;
}
