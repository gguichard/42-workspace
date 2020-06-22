#include "abstractvm.hpp"
#include "ioperand.hpp"
#include "operand.hpp"

#include <string>

AbstractVM::AbstractVM()
{
	m_operators[eOperandType::INT8] = &AbstractVM::createInt8;
	m_operators[eOperandType::INT16] = &AbstractVM::createInt16;
	m_operators[eOperandType::INT32] = &AbstractVM::createInt32;
	m_operators[eOperandType::FLOAT] = &AbstractVM::createFloat;
	m_operators[eOperandType::DOUBLE] = &AbstractVM::createDouble;
}

const IOperand *AbstractVM::createOperand(eOperandType type, const std::string &value) const
{
	return (this->*m_operators[type])(value);
}

const IOperand *AbstractVM::createInt8(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -128 || val > 127) { // bounds check
		throw std::runtime_error("int8 out of bounds");
	}
	return new Operand<eOperandType::INT8>(this, std::to_string(val));
}

const IOperand *AbstractVM::createInt16(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -32768 || val > 32767) { // bounds check
		throw std::runtime_error("int16 out of bounds");
	}
	return new Operand<eOperandType::INT16>(this, std::to_string(val));
}

const IOperand *AbstractVM::createInt32(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -2147483648 || val > 2147483647) { // bounds check
		throw std::runtime_error("int32 out of bounds");
	}
	return new Operand<eOperandType::INT32>(this, std::to_string(val));
}

const IOperand *AbstractVM::createFloat(const std::string &value) const
{
	float val = std::stof(value);

	return new Operand<eOperandType::FLOAT>(this, std::to_string(val));
}

const IOperand *AbstractVM::createDouble(const std::string &value) const
{
	double val = std::stod(value);

	return new Operand<eOperandType::DOUBLE>(this, std::to_string(val));
}
