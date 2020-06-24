#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

#include <stdexcept>
#include <string>

struct Symbol
{
	std::string identifier;
	Token::Type type;
};

class LexerException : public std::runtime_error
{
	using std::runtime_error::runtime_error;
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

	void skipComments();

	std::string extractIdentifier(const char *specialChars = "") const;

	Token atom(Token::Type tokenType);

	Token number();

	Token symbol();

private:
	std::string m_input;
	std::string::size_type m_position;
	bool m_hitEndInput;
};

#endif // LEXER_HPP
