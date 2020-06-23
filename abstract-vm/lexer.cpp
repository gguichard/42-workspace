#include "lexer.hpp"

#include <string>
#include <cstring>
#include <cctype>

static Symbol symbols[] = {
	{"int8", Token::Type::VAR_INT8},
	{"int16", Token::Type::VAR_INT16},
	{"int32", Token::Type::VAR_INT32},
	{"float", Token::Type::VAR_FLOAT},
	{"double", Token::Type::VAR_DOUBLE},
	{"push", Token::Type::OP_PUSH},
	{"pop", Token::Type::OP_POP},
	{"dump", Token::Type::OP_DUMP},
	{"assert", Token::Type::OP_ASSERT},
	{"add", Token::Type::OP_ADD},
	{"sub", Token::Type::OP_SUB},
	{"mul", Token::Type::OP_MUL},
	{"div", Token::Type::OP_DIV},
	{"mod", Token::Type::OP_MOD},
	{"print", Token::Type::OP_PRINT},
	{"exit", Token::Type::OP_EXIT}
};

Lexer::Lexer(std::string input)
	: m_input(std::move(input))
	, m_position(0)
{

}

const std::string &Lexer::getInput() const
{
	return m_input;
}

std::string::size_type Lexer::getPosition() const
{
	return m_position;
}

void Lexer::skipWhitespaces()
{
	while (m_position < m_input.size()) {
		if (!std::isspace(m_input.at(m_position))) {
			break;
		}
		m_position += 1;
	}
}

Token Lexer::atom(Token::Type tokenType)
{
	std::string lexeme = m_input.substr(m_position, 1);

	m_position += 1;
	return Token(tokenType, lexeme);
}

Token Lexer::number() // should match [-]?[0..9]+ (NUMBER_INTEGER) and [-]?[0..9]+.[0..9]+ (NUMBER_DOUBLE)
{
	int digits = 0;
	int decimalPoints = 0;
	std::string::size_type length = 0;
	std::string lexeme;

	if (m_input.at(m_position) == '-') {
		length += 1;
	}
	while ((m_position + length) < m_input.size()) {
		if (std::isdigit(m_input.at(m_position + length))) {
			digits++;
			length += 1;
		} else if (m_input.at(m_position + length) == '.') {
			digits = 0;
			decimalPoints++;
			length += 1;
		} else {
			break;
		}
	}
	lexeme = m_input.substr(m_position, length);
	if (digits == 0 || decimalPoints > 1) {
		throw LexerException("invalid number: " + lexeme);
	} else {
		m_position += length;
		if (decimalPoints != 0) {
			return Token(Token::Type::NUMBER_DOUBLE, lexeme);
		} else {
			return Token(Token::Type::NUMBER_INTEGER, lexeme);
		}
	}
}

Token Lexer::symbol()
{
	std::string::size_type length = 0;
	std::string lexeme;
	size_t idx;

	while ((m_position + length) < m_input.size()) {
		if (!std::isalnum(m_input.at(m_position + length))) { // our symbols only contains alpha numeric characters
			break;
		}
		length += 1;
	}
	lexeme = m_input.substr(m_position, length);
	for (idx = 0; idx < sizeof(symbols) / sizeof(symbols[0]); idx++) {
		if (lexeme == symbols[idx].identifier) {
			m_position += length;
			return Token(symbols[idx].type, lexeme);
		}
	}
	throw LexerException("invalid symbol: " + lexeme);
}

Token Lexer::nextToken()
{
	skipWhitespaces();

	if (m_position >= m_input.size()) {
		throw LexerException("end of input");
	}
	switch (m_input.at(m_position)) {
	case '(':
		return atom(Token::Type::OPEN_BRACKET);
	case ')':
		return atom(Token::Type::CLOSE_BRACKET);
	case ';':
		if ((m_position + 1) < m_input.size() && m_input.at(m_position + 1) == ';') {
			std::string lexeme = m_input.substr(m_position, 2);

			m_position += 2;
			return Token(Token::Type::END_SYMBOL, lexeme);
		}
		return atom(Token::Type::COMMENT_SYMBOL);
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
	case '-':
		return number();

	default:
		return symbol();
	}
}
