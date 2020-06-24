#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
	enum Type
	{
		END_OF_INPUT = 0,
		OP_PUSH,
		OP_POP,
		OP_DUMP,
		OP_ASSERT,
		OP_INCR,
		OP_DECR,
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_PRINT,
		OP_EXIT,
		VAR_INT8,
		VAR_INT16,
		VAR_INT32,
		VAR_FLOAT,
		VAR_DOUBLE,
		OPEN_BRACKET,
		CLOSE_BRACKET,
		NUMBER_INTEGER,
		NUMBER_DOUBLE,
		NEWLINE_SYMBOL
	};

	explicit Token(Token::Type type, std::string lexeme);

	Token::Type getType() const;

	const std::string &getLexeme() const;

private:
	Token::Type m_type;
	std::string m_lexeme;
};

#endif // TOKEN_HPP
