#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

#include <stdexcept>
#include <queue>

enum TokenValueOption
{
	NEEDED,
	OPTIONAL,
	NOT_NEEDED
};

struct InstrSymbol
{
	Token::Type tokenType;
	TokenValueOption valueOption;
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

	std::queue<Token> parseInput();

private:
	void eatToken();

	bool acceptToken(Token::Type tokenType);

	void skipNewlines();

	void parseNumber(Token::Type numberTokenType);

	void parseValue(TokenValueOption valueOption);

	bool parseInstr();

private:
	Lexer &m_lexer;
	Token m_currentToken;
	std::queue<Token> m_tokens;
};

#endif // PARSER_HPP
