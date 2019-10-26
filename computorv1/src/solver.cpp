#include <vector>
#include <iostream>
#include "solver.hpp"
#include "exprformula.hpp"
#include "complex.hpp"
#include "math.hpp"

Solver::Solver(std::string formula) : m_lexer(std::move(formula)), m_parser(m_lexer)
{
}

const Parser &Solver::parser() const
{
	return m_parser;
}

void Solver::solveQuadratic(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint) const
{
	double delta;

	math::solveQuadratic(expr.factorValue(2), expr.factorValue(1), expr.factorValue(0), delta, solutions);

	if (delta < 0)
		solutionHint = "Discriminant is strictly negative, the two complex solutions are:";
	else if (delta > 0)
		solutionHint = "Discriminant is strictly positive, the two real solutions are:";
	else
		solutionHint = "Discriminant is zero, the real solution is:";
}

void Solver::solveCubic(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint, bool debug) const
{
	double root;

	try
	{
		root = math::newtonRaphson(expr);
	}
	catch (std::runtime_error)
	{
		solutionHint = "Unable to find a root with Newton-Raphson method.";
		return;
	}

	solutions.emplace_back(root);

	if (math::abs(expr.factorValue(3)) < math::EPSILON)
		solutionHint = "The triple solution is:";
	else
	{
		double a = expr.factorValue(3);
		double b = expr.factorValue(2) + a * root;
		double c = expr.factorValue(1) + b * root;
		double delta;

		math::solveQuadratic(a, b, c, delta, solutions);

		if (debug)
			solutionHint = "Solving quadratic function: (X" + std::string(root < 0 ? "+" : "-") + std::to_string(math::abs(root)) + ")"
				+ "(" + std::to_string(a) + "X^2" + (b < 0 ? "" : "+") + std::to_string(b) + "X" + (c < 0 ? "" : "+") + std::to_string(c) + ") = 0"
				+ "\n";

		solutionHint += "The three solutions are:";
	}
}

void Solver::solve(bool debug)
{
	std::unique_ptr<BinaryOp> root = m_parser.poly();
	ExprFormula expr = (root->left().compute() - root->right().compute()).clean();

	if (expr.hasNegativePower())
		throw std::runtime_error("negative powers are not handled");

	if (debug)
		std::cout << *root << std::endl;

	std::vector<Complex> solutions;
	std::string solutionHint;

	solutions.reserve(3);

	switch (expr.degree())
	{
	case 0:
		if (expr.factorValue(0) != 0.0)
			solutionHint = "There is no solution.";
		else
			solutionHint = "Every complex number is a solution.";
		break;
	case 1:
		solutions.emplace_back(-expr.factorValue(0) / expr.factorValue(1));
		solutionHint = "The solution is:";
		break;
	case 2:
		solveQuadratic(expr, solutions, solutionHint);
		break;
	case 3:
		solveCubic(expr, solutions, solutionHint, debug);
		break;
	default:
		solutionHint = "Unable to solve because polynomial degree is greater than 3.";
		break;
	}

	printSolutions(expr, solutions, solutionHint);
}

void Solver::printSolutions(const ExprFormula &expr, std::vector<Complex> &solutions, std::string &solutionHint) const
{
	int nb = 0;

	std::cout << "Reduced form: " << expr << " = 0" << std::endl;
	std::cout << "Derivative function: " << expr.derivative() << std::endl;
	std::cout << "Polynomial degree: " << expr.degree() << std::endl;
	std::cout << solutionHint << std::endl;

	for (auto it = solutions.begin(); it < solutions.end(); it++)
	{
		std::cout << "X" << nb << " = " << *it << std::endl;
		nb += 1;
	}
}
