#include <vector>
#include "math.hpp"
#include "exprformula.hpp"
#include "complex.hpp"

namespace math
{
	double abs(double value)
	{
		if (value < 0)
			return -value;
		return value;
	}

	double pow(double n, int pow)
	{
		double result = 1;
		double factor = (pow < 0 ? (1 / n) : n);
		int incrPow = (pow < 0 ? 1 : -1);

		while (pow != 0)
		{
			result *= factor;
			pow += incrPow;
		}
		return result;
	}

	double modf(double value, double *iptr)
	{
		ieee_double conv;
		int exponent;

		conv.value = value;
		exponent = ((conv.word >> 52) & 0x7ff) - 0x3ff;
		if (exponent >= 52)
		{
			*iptr = value;
			if (exponent == (0x7ff - 0x3ff) && conv.word & 0xfffffffffffffUL)
				return value;
			conv.word &= 0x8000000000000000UL;
			return conv.value;
		}
		else
		{
			if (exponent < 0)
			{
				conv.word &= 0x8000000000000000UL;
				*iptr = conv.value;
				return value;
			}
			else
			{
				uint64_t mask = 0xfffffffffffffUL >> exponent;
				if ((conv.word & mask) == 0)
				{
					*iptr = value;
					conv.word &= 0x8000000000000000UL;
					return conv.value;
				}
				else
				{
					conv.word &= ~mask;
					*iptr = conv.value;
					return value - conv.value;
				}
			}
		}
	}

	double sqrt(double n)
	{
		double x0 = 1.0, x1 = 0.0;
		double integralPart;

		for (int iter = 0; iter < 20; iter++)
		{
			x1 = 0.5 * (x0 + n / x0);
			if (abs(x1 - x0) < EPSILON)
				break;
			x0 = x1;
		}
		if (abs(modf(x1, &integralPart)) < EPSILON)
			x1 = integralPart;
		return x1;
	}

	double newtonRaphson(const ExprFormula &expr)
	{
		int iter;
		double x0 = 1.0, x1 = 0.0;
		ExprFormula derivative = expr.derivative();
		double derivativeValue;
		double integralPart;

		// Search a root with Newton-Raphson method
		for (iter = 0; iter < 100; iter++)
		{
			derivativeValue = derivative.compute(x0);
			if (abs(derivativeValue) < 1e-14)
				break;
			x1 = x0 - expr.compute(x0) / derivativeValue;
			if (abs(x1 - x0) < EPSILON)
				break;
			x0 = x1;
		}
		if (iter == 100)
			throw std::runtime_error("unable to find root");
		else if (abs(modf(x1, &integralPart)) < EPSILON)
			x1 = integralPart;
		return x1;
	}

	void solveQuadratic(double a, double b, double c, double &delta, std::vector<Complex> &solutions)
	{
		double delta_sqrt;

		delta = b * b - 4 * a * c;
		if (delta < 0)
		{
			delta_sqrt = sqrt(-delta);
			solutions.emplace_back(-b / (2 * a), -delta_sqrt / (2 * a));
			solutions.emplace_back(-b / (2 * a), delta_sqrt / (2 * a));
		}
		else
		{
			delta_sqrt = sqrt(delta);
			solutions.emplace_back((-b - delta_sqrt) / (2 * a));
			if (delta > 0)
				solutions.emplace_back((-b + delta_sqrt) / (2 * a));
		}
	}
}
