#ifndef MATH_HPP
#define MATH_HPP

#include <vector>
#include "exprformula.hpp"
#include "complex.hpp"

namespace math
{
	const double EPSILON = 1e-6;

	union ieee_double
	{
		double value;
		uint64_t word;
	};

	double abs(double value);

	double pow(double n, int pow);

	double modf(double value, double *iptr);

	double sqrt(double n);

	double newtonRaphson(const ExprFormula &expr);

	void solveQuadratic(double a, double b, double c, double &delta, std::vector<Complex> &solutions);
}

#endif // MATH_HPP
