#include "abstractvm.hpp"
#include "ioperand.hpp"
#include "operand.hpp"
#include "token.hpp"

#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <memory>
#include <iostream>

TokenOperand tokenOperand[] = {
	{Token::Type::VAR_INT8, eOperandType::INT8},
	{Token::Type::VAR_INT16, eOperandType::INT16},
	{Token::Type::VAR_INT32, eOperandType::INT32},
	{Token::Type::VAR_FLOAT, eOperandType::FLOAT},
	{Token::Type::VAR_DOUBLE, eOperandType::DOUBLE}
};

TokenDispatcher tokenDispatcher[] = {
	{Token::Type::OP_PUSH, &AbstractVM::pushOperation},
	{Token::Type::OP_POP, &AbstractVM::popOperation},
	{Token::Type::OP_DUMP, &AbstractVM::dumpOperation},
	{Token::Type::OP_ASSERT, &AbstractVM::assertOperation},
	{Token::Type::OP_ADD, &AbstractVM::addOperation},
	{Token::Type::OP_SUB, &AbstractVM::subOperation},
	{Token::Type::OP_MUL, &AbstractVM::mulOperation},
	{Token::Type::OP_DIV, &AbstractVM::divOperation},
	{Token::Type::OP_MOD, &AbstractVM::modOperation},
	{Token::Type::OP_PRINT, &AbstractVM::printOperation},
	{Token::Type::OP_EXIT, &AbstractVM::exitOperation}
};

AbstractVM::AbstractVM()
{
	m_operators[eOperandType::INT8] = &AbstractVM::createInt8;
	m_operators[eOperandType::INT16] = &AbstractVM::createInt16;
	m_operators[eOperandType::INT32] = &AbstractVM::createInt32;
	m_operators[eOperandType::FLOAT] = &AbstractVM::createFloat;
	m_operators[eOperandType::DOUBLE] = &AbstractVM::createDouble;
}

AbstractVM::~AbstractVM()
{
	while (!m_stack.empty()) {
		delete m_stack.top();

		m_stack.pop();
	}
}

const IOperand *AbstractVM::createOperand(eOperandType type, const std::string &value) const
{
	try {
		return (this->*m_operators[type])(value);
	} catch (std::invalid_argument &e) {
		throw VMException("invalid number");
	} catch (std::out_of_range &e) {
		throw VMException("number out of range");
	}
}

void AbstractVM::run(std::queue<Token> &tokens)
{
	size_t idx;

	m_exit = false;
	while (!tokens.empty()) {
		Token::Type tokenType = tokens.front().getType();

		tokens.pop();
		for (idx = 0; idx < sizeof(tokenDispatcher) / sizeof(tokenDispatcher[0]); idx++) {
			if (tokenDispatcher[idx].tokenType == tokenType) {
				(this->*tokenDispatcher[idx].fn)(tokens);
				break;
			}
		}
	}
	if (!m_exit) {
		throw VMException("no exit instruction");
	}
}

const std::unique_ptr<const IOperand> AbstractVM::popStack()
{
	const IOperand *operand;

	if (m_stack.empty()) {
		throw StackException("pop on empty stack");
	}
	operand = m_stack.top();
	m_stack.pop();
	return std::unique_ptr<const IOperand>(operand);
}

const IOperand *AbstractVM::popOperand(std::queue<Token> &tokens)
{
	size_t idx;
	Token::Type tokenType = tokens.front().getType();

	tokens.pop();
	for (idx = 0; idx < sizeof(tokenOperand) / sizeof(tokenOperand[0]); idx++) {
		if (tokenType == tokenOperand[idx].tokenType) {
			std::string number = tokens.front().getLexeme();

			tokens.pop();
			return createOperand(tokenOperand[idx].operandType, number);
		}
	}
	throw VMException("expected var type token");
}

void AbstractVM::pushOperation(std::queue<Token> &tokens)
{
	m_stack.push(popOperand(tokens));
}

void AbstractVM::popOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	popStack();
}

void AbstractVM::dumpOperation(std::queue<Token> &tokens)
{
	(void)tokens;
	std::stack<const IOperand *> stack;

	while (!m_stack.empty()) {
		stack.push(m_stack.top());
		std::cout << m_stack.top()->toString() << std::endl;
		m_stack.pop();
	}
	while (!stack.empty()) {
		m_stack.push(stack.top());
		stack.pop();
	}
}

void AbstractVM::assertOperation(std::queue<Token> &tokens)
{
	if (m_stack.empty()) {
		throw StackException("assert on empty stack");
	} else {
		const IOperand *top = m_stack.top();
		std::unique_ptr<const IOperand> operand(popOperand(tokens));

		if (top->getType() != operand->getType() || top->toString() != operand->toString()) {
			throw StackException("top stack assert failed");
		}
	}
}

void AbstractVM::addOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.size() < 2) {
		throw StackException("add operation stack error");
	}
	m_stack.push(*popStack() + *popStack());
}

void AbstractVM::subOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.size() < 2) {
		throw StackException("sub operation stack error");
	}
	m_stack.push(*popStack() - *popStack());
}

void AbstractVM::mulOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.size() < 2) {
		throw StackException("mul operation stack error");
	}
	m_stack.push(*popStack() * *popStack());
}

void AbstractVM::divOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.size() < 2) {
		throw StackException("div operation stack error");
	}
	m_stack.push(*popStack() / *popStack());
}

void AbstractVM::modOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.size() < 2) {
		throw StackException("mod operation stack error");
	}
	m_stack.push(*popStack() % *popStack());
}

void AbstractVM::printOperation(std::queue<Token> &tokens)
{
	(void)tokens;

	if (m_stack.empty()) {
		throw StackException("print on empty stack");
	} else {
		const IOperand *top = m_stack.top();

		if (top->getType() != eOperandType::INT8) {
			throw StackException("print: stack top must be int8");
		}
		std::cout << static_cast<char>(std::stoi(top->toString())) << std::endl;
	}
}

void AbstractVM::exitOperation(std::queue<Token> &tokens)
{
	m_exit = true;

	while (!tokens.empty()) {
		tokens.pop();
	}
}

const IOperand *AbstractVM::createInt8(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -128 || val > 127) { // bounds check
		throw VMException("int8 out of bounds");
	}
	return new Operand<eOperandType::INT8>(this, std::to_string(val));
}

const IOperand *AbstractVM::createInt16(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -32768 || val > 32767) { // bounds check
		throw VMException("int16 out of bounds");
	}
	return new Operand<eOperandType::INT16>(this, std::to_string(val));
}

const IOperand *AbstractVM::createInt32(const std::string &value) const
{
	int val = std::stoll(value);

	if (val < -2147483648 || val > 2147483647) { // bounds check
		throw VMException("int32 out of bounds");
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
