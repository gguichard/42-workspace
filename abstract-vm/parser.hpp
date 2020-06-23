#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

#include <stdexcept>

struct InstrSymbol
{
	Token::Type tokenType;
	bool value;
};

struct ValueSymbol
{
	Token::Type tokenType;
	Token::Type numberTokenType;
};

class ParserException : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

class Parser
{
public:
	explicit Parser(Lexer &lexer);

	void parseInput();

private:
	void eatToken();

	bool acceptToken(Token::Type tokenType);

	void skipNewlines();

	void parseNumber(Token::Type numberTokenType);

	void parseValue();

	bool parseInstr();

private:
	Lexer &m_lexer;
	Token m_currentToken;
};

#endif // PARSER_HPP
