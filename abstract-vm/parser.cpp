#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"

#include <cstring>

InstrSymbol instrSymbols[] = {
	{Token::Type::OP_PUSH, true},
	{Token::Type::OP_POP, false},
	{Token::Type::OP_DUMP, false},
	{Token::Type::OP_ASSERT, true},
	{Token::Type::OP_ADD, false},
	{Token::Type::OP_SUB, false},
	{Token::Type::OP_MUL, false},
	{Token::Type::OP_DIV, false},
	{Token::Type::OP_MOD, false},
	{Token::Type::OP_PRINT, false},
	{Token::Type::OP_EXIT, false}
};

ValueSymbol valueSymbols[] = {
	{Token::Type::VAR_INT8, Token::Type::NUMBER_INTEGER},
	{Token::Type::VAR_INT16, Token::Type::NUMBER_INTEGER},
	{Token::Type::VAR_INT32, Token::Type::NUMBER_INTEGER},
	{Token::Type::VAR_FLOAT, Token::Type::NUMBER_DOUBLE},
	{Token::Type::VAR_DOUBLE, Token::Type::NUMBER_DOUBLE}
};

Parser::Parser(Lexer &lexer)
	: m_lexer(lexer)
	, m_currentToken(lexer.nextToken()) // init first token
{

}

void Parser::eatToken()
{
	m_currentToken = m_lexer.nextToken();
}

bool Parser::acceptToken(Token::Type tokenType)
{
	if (m_currentToken.getType() == tokenType) {
		eatToken();
		return true;
	}
	return false;
}

void Parser::skipNewlines()
{
	while (m_currentToken.getType() == Token::Type::NEWLINE_SYMBOL) {
		eatToken();
	}
}

void Parser::parseNumber(Token::Type numberTokenType)
{
	if (!acceptToken(Token::Type::OPEN_BRACKET)) {
		throw ParserException("expected left parenthesis");
	}
	if (!acceptToken(numberTokenType)) {
		switch (numberTokenType) {
		case Token::Type::NUMBER_DOUBLE:
			throw ParserException("expected real number");
		case Token::Type::NUMBER_INTEGER:
			throw ParserException("expected integer number");

		default:
			throw ParserException("expected number"); // should never happen
		}
	}
	if (!acceptToken(Token::Type::CLOSE_BRACKET)) {
		throw ParserException("expected right parenthesis");
	}
}

void Parser::parseValue()
{
	size_t idx;

	for (idx = 0; idx < sizeof(valueSymbols) / sizeof(valueSymbols[0]); idx++) {
		if (acceptToken(valueSymbols[idx].tokenType)) {
			parseNumber(valueSymbols[idx].numberTokenType);
			return;
		}
	}
	throw ParserException("expected value type (eg: int8, int16...)");
}

bool Parser::parseInstr()
{
	size_t idx;

	for (idx = 0; idx < sizeof(instrSymbols) / sizeof(instrSymbols[0]); idx++) {
		if (acceptToken(instrSymbols[idx].tokenType)) {
			if (instrSymbols[idx].value) {
				parseValue();
			}
			return true;
		}
	}
	return false;
}

void Parser::parseInput()
{
	if (!parseInstr()) {
		throw ParserException("expected instr symbol (eg: push, pop...)");
	}
	while (m_currentToken.getType() != Token::Type::END_OF_INPUT) {
		if (!acceptToken(Token::Type::NEWLINE_SYMBOL)) {
			throw ParserException("expected newline");
		}
		skipNewlines(); // skip additional newlines
		parseInstr();
	}
}
