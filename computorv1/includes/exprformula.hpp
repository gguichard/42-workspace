#ifndef EXPRFORMULA_H
#define EXPRFORMULA_H

#include <vector>
#include <iostream>

class ExprFormula
{
public:
	struct Factor
	{		
		explicit Factor(double newValue = 0.0, int newPower = 0);

		double value;
		int power;
	};

	explicit ExprFormula();

	int degree() const;
	double compute(double x) const;
	bool hasUnknownPower() const;
	bool hasNegativePower() const;

	ExprFormula clean() const;
	ExprFormula derivative() const;

	Factor &factor(int pow);
	double factorValue(int pow, double def = 0) const;

	ExprFormula operator-() const;
	ExprFormula operator+(const ExprFormula expr2) const;
	ExprFormula operator-(const ExprFormula expr2) const;
	ExprFormula operator*(const ExprFormula expr2) const;
	ExprFormula operator/(const ExprFormula expr2) const;
	ExprFormula operator^(const ExprFormula expr2) const;
	friend std::ostream &operator<<(std::ostream &, const ExprFormula &);

private:
	std::vector<ExprFormula::Factor> m_factors;
};

#endif // EXPRFORMULA_H
