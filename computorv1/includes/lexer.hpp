#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "token.hpp"

class Lexer
{
public:
	explicit Lexer(const std::string formula);

	const std::string &formula() const;
	std::string::size_type offset() const;

	Token nextToken();

private:
	void skipWhitespaces();

	Token atom(Token::Type type);
	Token number();

private:
	const std::string m_formula;
	std::string::size_type m_offset = 0;
};

#endif // LEXER_HPP
