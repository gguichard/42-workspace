#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

enum eOperandType
{
	INT8 = 1,
	INT16 = 2,
	INT32 = 3,
	FLOAT = 4,
	DOUBLE = 5,
	UNKNOWN = 10,
	LAST_OPERAND = 11
};

class IOperand
{
public:
	virtual ~IOperand() = default;

	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;

	virtual const IOperand *operator+(const IOperand &rhs) const = 0;
	virtual const IOperand *operator-(const IOperand &rhs) const = 0;
	virtual const IOperand *operator*(const IOperand &rhs) const = 0;
	virtual const IOperand *operator/(const IOperand &rhs) const = 0;
	virtual const IOperand *operator%(const IOperand &rhs) const = 0;

	virtual const std::string &toString() const = 0;
};

#endif // IOPERAND_HPP
