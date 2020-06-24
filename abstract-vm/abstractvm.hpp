#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "ioperand.hpp"
#include "token.hpp"

#include <string>
#include <queue>
#include <stack>
#include <stdexcept>
#include <memory>

class VMException : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

class StackException : public VMException
{
	using VMException::VMException;
};

class AbstractVM
{
public:
	explicit AbstractVM();
	~AbstractVM();

	const IOperand *createOperand(eOperandType type, const std::string &value) const;

	void run(std::queue<Token> &tokens);

	// stack operations
	void pushOperation(std::queue<Token> &tokens);
	void popOperation(std::queue<Token> &tokens);
	void dumpOperation(std::queue<Token> &tokens);
	void assertOperation(std::queue<Token> &tokens);
	void addOperation(std::queue<Token> &tokens);
	void subOperation(std::queue<Token> &tokens);
	void mulOperation(std::queue<Token> &tokens);
	void divOperation(std::queue<Token> &tokens);
	void modOperation(std::queue<Token> &tokens);
	void printOperation(std::queue<Token> &tokens);
	void exitOperation(std::queue<Token> &tokens);

private:
	const std::unique_ptr<const IOperand> popStack();
	const IOperand *popOperand(std::queue<Token> &tokens);

	// operands
	const IOperand *createInt8(const std::string &value) const;
	const IOperand *createInt16(const std::string &value) const;
	const IOperand *createInt32(const std::string &value) const;
	const IOperand *createFloat(const std::string &value) const;
	const IOperand *createDouble(const std::string &value) const;

private:
	const IOperand *(AbstractVM::*m_operators[eOperandType::LAST_OPERAND])(const std::string &) const;
	std::stack<const IOperand *> m_stack;
	bool m_exit;
};

struct TokenOperand
{
	Token::Type tokenType;
	eOperandType operandType;
};

struct TokenDispatcher
{
	Token::Type tokenType;
	void (AbstractVM::*fn)(std::queue<Token> &tokens);
};

#endif // ABSTRACTVM_HPP
