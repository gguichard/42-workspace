#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

#include <string>

struct Symbol
{
	std::string identifier;
	Token::Type type;
};

class Lexer
{
public:
	explicit Lexer(std::string input);

	const std::string &getInput() const;

	std::string::size_type getPosition() const;

	Token nextToken();

private:
	void skipWhitespaces();

	Token atom(Token::Type tokenType);

	Token number();

	Token symbol();

private:
	std::string m_input;
	std::string::size_type m_position;
};

#endif // LEXER_HPP
