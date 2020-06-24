#include "lexer.hpp"

#include <string>
#include <regex>
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
	{"incr", Token::Type::OP_INCR},
	{"decr", Token::Type::OP_DECR},
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
		if (std::strchr(" \t\v\f\r", m_input.at(m_position)) == nullptr) { // whitespaces without \n
			break;
		}
		m_position += 1;
	}
}

void Lexer::skipComments()
{
	while (m_position < m_input.size() && m_input.at(m_position) == ';') {
		while (m_position < m_input.size()) {
			m_position += 1;
			if (m_input.at(m_position - 1) == '\n') {
				break;
			}
		}
	}
}

std::string Lexer::extractIdentifier(const char *specialChars) const
{
	std::string::size_type length = 0;
	std::string identifier;

	while ((m_position + length) < m_input.size()) {
		if (!std::isalnum(m_input.at(m_position + length)) // our identifiers only contains alpha numeric characters
			&& std::strchr(specialChars, m_input.at(m_position + length)) == nullptr) {
			break;
		}
		length += 1;
	}
	identifier = m_input.substr(m_position, length);
	return identifier;
}

Token Lexer::atom(Token::Type tokenType)
{
	std::string lexeme = m_input.substr(m_position, 1);

	m_position += 1;
	return Token(tokenType, lexeme);
}

Token Lexer::number()
{
	std::regex intRegex("[-]?[0-9]+");
	std::regex doubleRegex("[-]?[0-9]+.[0-9]+");
	std::string lexeme = extractIdentifier("-.");

	if (!std::regex_match(lexeme, intRegex) && !std::regex_match(lexeme, doubleRegex)) {
		throw LexerException("invalid number: " + lexeme);
	} else {
		m_position += lexeme.size();
		if (lexeme.find_first_of(".") != std::string::npos) {
			return Token(Token::Type::NUMBER_DOUBLE, lexeme);
		} else {
			return Token(Token::Type::NUMBER_INTEGER, lexeme);
		}
	}
}

Token Lexer::symbol()
{
	std::string lexeme;
	size_t idx;

	lexeme = extractIdentifier();
	for (idx = 0; idx < sizeof(symbols) / sizeof(symbols[0]); idx++) {
		if (lexeme == symbols[idx].identifier) {
			m_position += lexeme.size();
			return Token(symbols[idx].type, lexeme);
		}
	}
	throw LexerException("invalid symbol: " + lexeme);
}

Token Lexer::nextToken()
{
	std::string::size_type oldPosition = std::string::npos;

	while (oldPosition != m_position) {
		oldPosition = m_position;
		skipWhitespaces();
		skipComments();
	}
	if (m_position == std::string::npos) {
		throw LexerException("end of input");
	} else if (m_position >= m_input.size()) {
		m_position = std::string::npos;
		return Token(Token::Type::END_OF_INPUT, "");
	}
	switch (m_input.at(m_position)) {
	case '\n':
		return atom(Token::Type::NEWLINE_SYMBOL);
	case '(':
		return atom(Token::Type::OPEN_BRACKET);
	case ')':
		return atom(Token::Type::CLOSE_BRACKET);
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
