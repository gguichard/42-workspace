#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "exprformula.hpp"
#include "complex.hpp"

class Solver
{
public:
	explicit Solver(std::string formula);

	void solve(bool debug);

	const Parser &parser() const;

private:
	void solveQuadratic(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint) const;
	void solveCubic(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint, bool debug) const;

	void printSolutions(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint) const;

private:
	Lexer m_lexer;
	Parser m_parser;
};

#endif // SOLVER_HPP
