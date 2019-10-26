#ifndef PARSER_HPP
#define PARSER_HPP

#include <stdexcept>
#include <memory>
#include "lexer.hpp"
#include "token.hpp"
#include "astnode.hpp"
#include "binaryop.hpp"

class ParserException : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

class Parser
{
public:
	explicit Parser(Lexer &lexer);

	std::unique_ptr<BinaryOp> poly();

	void printError(ParserException &e) const;

private:
	void eatToken();
	bool acceptToken(Token::Type tokenType);

	std::unique_ptr<ASTNode> factor(int depth);
	std::unique_ptr<ASTNode> term(int depth);
	std::unique_ptr<ASTNode> expr(int depth);
	std::unique_ptr<ASTNode> expectExpr();

private:
	Lexer &m_lexer;
	Token m_currentToken;
};

#endif // PARSER_HPP
