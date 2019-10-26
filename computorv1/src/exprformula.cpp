#include <vector>
#include <iostream>
#include <algorithm>
#include "exprformula.hpp"
#include "math.hpp"

ExprFormula::Factor::Factor(double newValue, int newPower) : value(newValue), power(newPower)
{
}

ExprFormula::ExprFormula()
{
}

int ExprFormula::degree() const
{
	int degree = 0;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
	{
		if (degree < it->power)
			degree = it->power;
	}
	return degree;
}

double ExprFormula::compute(double x) const
{
	double total = 0;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
		total += it->value * math::pow(x, it->power);

	return total;
}

bool ExprFormula::hasPowerFactor() const
{
	return std::find_if(m_factors.begin(), m_factors.end(),
		[](const Factor &f) -> bool { return f.power != 0 && f.value != 0.0; }) != m_factors.end();
}

bool ExprFormula::hasNegativePower() const
{
	return std::find_if(m_factors.begin(), m_factors.end(),
		[](const Factor &f) -> bool { return f.power < 0 && f.value != 0.0; }) != m_factors.end();
}

ExprFormula ExprFormula::clean() const
{
	ExprFormula expr;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
	{
		if (it->value == 0.0)
			continue;

		expr.factor(it->power).value = it->value;
	}

	std::sort(expr.m_factors.begin(), expr.m_factors.end(),
		[](ExprFormula::Factor &f1, ExprFormula::Factor &f2) { return f1.power > f2.power; });

	return expr;
}

ExprFormula ExprFormula::derivative() const
{
	ExprFormula expr;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
	{
		if (it->power > 0)
			expr.factor(it->power - 1).value += it->value * it->power;
	}
	return expr;
}

ExprFormula::Factor &ExprFormula::factor(int pow)
{
	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
	{
		if (it->power == pow)
			return *it;
	}
	return m_factors.emplace_back(0.0, pow);
}

double ExprFormula::factorValue(int pow, double def) const
{
	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
	{
		if (it->power == pow)
			return it->value;
	}
	return def;
}

ExprFormula ExprFormula::operator-() const
{
	ExprFormula expr;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
		expr.factor(it->power).value = -it->value;

	return expr;
}

ExprFormula ExprFormula::operator+(const ExprFormula expr2) const
{
	ExprFormula expr;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
		expr.factor(it->power).value += it->value;
	for (auto it = expr2.m_factors.begin(); it < expr2.m_factors.end(); it++)
		expr.factor(it->power).value += it->value;

	return expr;
}

ExprFormula ExprFormula::operator-(const ExprFormula expr2) const
{
	ExprFormula expr;

	for (auto it = m_factors.begin(); it < m_factors.end(); it++)
		expr.factor(it->power).value += it->value;
	for (auto it = expr2.m_factors.begin(); it < expr2.m_factors.end(); it++)
		expr.factor(it->power).value -= it->value;

	return expr;
}

ExprFormula ExprFormula::operator*(const ExprFormula expr2) const
{
	ExprFormula expr;

	for (auto it1 = m_factors.begin(); it1 < m_factors.end(); it1++)
	{
		for (auto it2 = expr2.m_factors.begin(); it2 < expr2.m_factors.end(); it2++)
			expr.factor(it1->power + it2->power).value += it1->value * it2->value;
	}
	return expr;
}

ExprFormula ExprFormula::operator/(const ExprFormula expr2) const
{
	auto predicate = [](const Factor &f) -> bool { return f.value != 0.0; };
	auto dn = std::find_if(expr2.m_factors.begin(), expr2.m_factors.end(), predicate);

	if (dn == expr2.m_factors.end())
		throw std::logic_error("division by zero");
	else if (std::count_if(expr2.m_factors.begin(), expr2.m_factors.end(), predicate) > 1)
		throw std::logic_error("only one factor is allowed as fraction denominator");

	ExprFormula expr;

	for (auto nm = m_factors.begin(); nm < m_factors.end(); nm++)
		expr.factor(nm->power - dn->power).value += nm->value / dn->value;

	return expr;
}

ExprFormula ExprFormula::operator^(const ExprFormula expr2) const
{
	if (expr2.hasPowerFactor())
		throw std::logic_error("unable to use X as pow factor");

	double integralPow;

	if (math::modf(expr2.factorValue(0), &integralPow) != 0.0)
		throw std::logic_error("can only pow by integer power");

	ExprFormula expr;
	int pow = int(integralPow);
	int incrPow = (pow < 0 ? 1 : -1);

	expr.factor(0).value = 1.0;
	while (pow != 0)
	{
		if (pow < 0)
			expr = expr / *this;
		else
			expr = expr * *this;
		pow += incrPow;
	}
	return expr;
}

std::ostream &operator<<(std::ostream &os, const ExprFormula &expr)
{
	if (expr.m_factors.empty())
		os << "0";
	for (auto it = expr.m_factors.begin(); it < expr.m_factors.end(); it++)
	{
		if (it != expr.m_factors.begin() || it->value < 0)
			os << (it->value < 0 ? "-" : "+");
		if (it->power == 0 || math::abs(it->value) != 1.0)
			os << math::abs(it->value);
		if (it->power != 0)
		{
			os << "X";
			if (it->power != 1)
				os << "^" << it->power;
		}
	}
	return os;
}
