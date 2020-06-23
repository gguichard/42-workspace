#include "token.hpp"

Token::Token(Token::Type type, std::string lexeme)
	: m_type(type)
	, m_lexeme(std::move(lexeme))
{

}

Token::Type Token::getType() const
{
	return m_type;
}

const std::string &Token::getLexeme() const
{
	return m_lexeme;
}
