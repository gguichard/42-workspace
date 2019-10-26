#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <ostream>

class Token
{
public:
	enum class Type
	{
		OPEN_BRACKET,
		CLOSE_BRACKET,
		NUMBER,
		VAR,
		OP_PLUS,
		OP_MINUS,
		OP_MUL,
		OP_DIV,
		OP_POW,
		OP_EQUALITY,
		END,
		UNKNOWN
	};

	explicit Token(Token::Type type, std::string lexeme);

	Token::Type type() const;
	const std::string &lexeme() const;

	bool isType(Token::Type tokenType) const;

	friend std::ostream &operator <<(std::ostream &os, const Token &token);

private:
	Token::Type m_type;
	std::string m_lexeme;
};

#endif // TOKEN_HPP
