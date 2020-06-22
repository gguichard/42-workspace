#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "ioperand.hpp"

#include <string>

class AbstractVM
{
public:
	explicit AbstractVM();

	const IOperand *createOperand(eOperandType type, const std::string &value) const;

private:
	const IOperand *createInt8(const std::string &value) const;
	const IOperand *createInt16(const std::string &value) const;
	const IOperand *createInt32(const std::string &value) const;
	const IOperand *createFloat(const std::string &value) const;
	const IOperand *createDouble(const std::string &value) const;

private:
	const IOperand *(AbstractVM::*m_operators[eOperandType::LAST_OPERAND])(const std::string &) const;
};

#endif // ABSTRACTVM_HPP
