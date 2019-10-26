#include <string>
#include <ostream>
#include "token.hpp"

Token::Token(Token::Type type, std::string lexeme) : m_type(type), m_lexeme(lexeme)
{
}

Token::Type Token::type() const
{
	return m_type;
}

const std::string &Token::lexeme() const
{
	return m_lexeme;
}

bool Token::isType(Token::Type tokenType) const
{
	return m_type == tokenType;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
	os << token.m_lexeme;
	return os;
}
