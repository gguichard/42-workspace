#include <string>
#include <vector>
#include "lexer.hpp"
#include "token.hpp"

Lexer::Lexer(const std::string formula) : m_formula(formula)
{
}

Token Lexer::atom(Token::Type tokenType)
{
	Token token(tokenType, m_formula.substr(m_offset, 1));

	m_offset += 1;
	return token;
}

Token Lexer::number()
{
	std::string::size_type offset = m_offset;
	int dots = 0;

	while (m_offset < m_formula.length())
	{
		if (std::isdigit(m_formula.at(m_offset)))
			m_offset += 1;
		else if (m_formula.at(m_offset) == '.')
		{
			if (++dots > 1)
				break;
			m_offset += 1;
		}
		else
			break;
	}
	return Token(Token::Type::NUMBER, m_formula.substr(offset, m_offset - offset));
}

void Lexer::skipWhitespaces()
{
	while (m_offset < m_formula.length())
	{
		if (!std::isspace(m_formula.at(m_offset)))
			break;
		m_offset += 1;
	}
}

const std::string &Lexer::formula() const
{
	return m_formula;
}

std::string::size_type Lexer::offset() const
{
	return m_offset;
}

Token Lexer::nextToken()
{
	skipWhitespaces();

	if (m_offset >= m_formula.length())
		return Token(Token::Type::END, "?");

	switch (m_formula.at(m_offset))
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		return number();
	case 'x':
	case 'X':
		return atom(Token::Type::VAR);
	case '(':
	case '[':
		return atom(Token::Type::OPEN_BRACKET);
	case ')':
	case ']':
		return atom(Token::Type::CLOSE_BRACKET);
	case '+':
		return atom(Token::Type::OP_PLUS);
	case '-':
		return atom(Token::Type::OP_MINUS);
	case '*':
		return atom(Token::Type::OP_MUL);
	case '/':
		return atom(Token::Type::OP_DIV);
	case '^':
		return atom(Token::Type::OP_POW);
	case '=':
		return atom(Token::Type::OP_EQUALITY);
	default:
		return atom(Token::Type::UNKNOWN);
	}
}
