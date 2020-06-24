#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "abstractvm.hpp"
#include "ioperand.hpp"

#include <string>
#include <cmath>

template <eOperandType T>
class Operand : public IOperand
{
public:
	explicit Operand();
	explicit Operand(const Operand &operand) = default;
	virtual ~Operand() = default;
	Operand &operator=(const Operand &operand) = default;

	explicit Operand(const AbstractVM *factory, std::string value);

	virtual int getPrecision() const override;
	virtual eOperandType getType() const override;

	virtual const IOperand *operator+(const IOperand &rhs) const override;
	virtual const IOperand *operator-(const IOperand &rhs) const override;
	virtual const IOperand *operator*(const IOperand &rhs) const override;
	virtual const IOperand *operator/(const IOperand &rhs) const override;
	virtual const IOperand *operator%(const IOperand &rhs) const override;

	virtual const std::string &toString() const override;

private:
	eOperandType getHighestPriority(const IOperand &rhs) const;

private:
	const AbstractVM *m_factory;
	std::string m_value;
};

template <eOperandType T>
Operand<T>::Operand()
{
	throw std::logic_error("default constructor not implemented");
}

template <eOperandType T>
Operand<T>::Operand(const AbstractVM *factory, std::string value)
	: m_factory(factory),
	  m_value(std::move(value))
{

}

template <eOperandType T>
int Operand<T>::getPrecision() const
{
	return 0;
}

template <eOperandType T>
eOperandType Operand<T>::getType() const
{
	return T;
}

template <eOperandType T>
eOperandType Operand<T>::getHighestPriority(const IOperand &rhs) const
{
	return std::max(getType(), rhs.getType());
}

template <eOperandType T>
const IOperand *Operand<T>::operator+(const IOperand &rhs) const
{
	double result = std::stod(toString()) + std::stod(rhs.toString());

	return m_factory->createOperand(getHighestPriority(rhs), std::to_string(result));
}

template <eOperandType T>
const IOperand *Operand<T>::operator-(const IOperand &rhs) const
{
	double result = std::stod(toString()) - std::stod(rhs.toString());

	return m_factory->createOperand(getHighestPriority(rhs), std::to_string(result));
}

template <eOperandType T>
const IOperand *Operand<T>::operator*(const IOperand &rhs) const
{
	double result = std::stod(toString()) * std::stod(rhs.toString());

	return m_factory->createOperand(getHighestPriority(rhs), std::to_string(result));
}

template <eOperandType T>
const IOperand *Operand<T>::operator/(const IOperand &rhs) const
{
	double result;
	eOperandType type = getHighestPriority(rhs);

	if (type < eOperandType::FLOAT && std::stoll(rhs.toString()) == 0) {
		throw VMException("division by zero");
	}
	result = std::stod(toString()) / std::stod(rhs.toString());
	return m_factory->createOperand(type, std::to_string(result));
}

template <eOperandType T>
const IOperand *Operand<T>::operator%(const IOperand &rhs) const
{
	double result;
	eOperandType type = getHighestPriority(rhs);

	if (type < eOperandType::FLOAT && std::stoll(rhs.toString()) == 0) {
		throw VMException("modulo by zero");
	}
	result = std::fmod(std::stod(toString()), std::stod(rhs.toString()));
	return m_factory->createOperand(type, std::to_string(result));
}

template <eOperandType T>
const std::string &Operand<T>::toString() const
{
	return m_value;
}

#endif // OPERAND_HPP
