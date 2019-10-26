#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "astnode.hpp"
#include "number.hpp"
#include "binaryop.hpp"
#include "unaryop.hpp"

Parser::Parser(Lexer &lexer) : m_lexer(lexer), m_currentToken(lexer.nextToken())
{
}

void Parser::eatToken()
{
	m_currentToken = m_lexer.nextToken();
}

bool Parser::acceptToken(Token::Type tokenType)
{
	if (m_currentToken.isType(tokenType))
	{
		eatToken();
		return true;
	}
	return false;
}

std::unique_ptr<ASTNode> Parser::factor(int depth)
{
	std::unique_ptr<ASTNode> node = nullptr;

	if (depth > 512)
		throw std::runtime_error("max depth reached (512)");

	if (m_currentToken.isType(Token::Type::VAR) || m_currentToken.isType(Token::Type::NUMBER))
	{
		node = std::make_unique<Number>(m_currentToken);
		eatToken();
	}
	else if (m_currentToken.isType(Token::Type::OP_PLUS) || m_currentToken.isType(Token::Type::OP_MINUS))
	{
		Token token = std::move(m_currentToken);

		eatToken();
		node = factor(depth + 1);
		if (node == nullptr)
			throw ParserException("expected factor after unary operator");

		node = std::make_unique<UnaryOp>(token, node);
	}
	else if (m_currentToken.isType(Token::Type::OPEN_BRACKET))
	{
		eatToken();
		node = expr(depth + 1);
		if (node == nullptr)
			throw ParserException("expected expr inside brackets");
		else if (!acceptToken(Token::Type::CLOSE_BRACKET))
			throw ParserException("expected close bracket");
	}
	if (node != nullptr && m_currentToken.isType(Token::Type::OP_POW))
	{
		Token token = std::move(m_currentToken);
		std::unique_ptr<ASTNode> powFactor = nullptr;

		eatToken();
		powFactor = factor(depth + 1);
		if (powFactor == nullptr)
			throw ParserException("expected power factor");

		node = std::make_unique<BinaryOp>(token, node, powFactor);
	}
	return node;
}

std::unique_ptr<ASTNode> Parser::term(int depth)
{
	std::unique_ptr<ASTNode> node = factor(depth + 1);

	while (m_currentToken.isType(Token::Type::OP_MUL) || m_currentToken.isType(Token::Type::OP_DIV)
		   || m_currentToken.isType(Token::Type::VAR) || m_currentToken.isType(Token::Type::OPEN_BRACKET))
	{
		if (node == nullptr)
			throw ParserException("term must begin with a factor");

		Token token = Token(Token::Type::OP_MUL, "*");
		std::unique_ptr<ASTNode> termFactor = nullptr;

		if (m_currentToken.isType(Token::Type::OP_MUL) || m_currentToken.isType(Token::Type::OP_DIV))
		{
			token = std::move(m_currentToken);
			eatToken();
		}

		termFactor = factor(depth + 1);
		if (termFactor == nullptr)
			throw ParserException("expected factor");

		node = std::make_unique<BinaryOp>(token, node, termFactor);
	}
	return node;
}

std::unique_ptr<ASTNode> Parser::expr(int depth)
{
	std::unique_ptr<ASTNode> node = term(depth + 1);

	while (m_currentToken.isType(Token::Type::OP_PLUS) || m_currentToken.isType(Token::Type::OP_MINUS))
	{
		if (node == nullptr)
			throw ParserException("expr must begin with a term");

		Token token = std::move(m_currentToken);
		std::unique_ptr<ASTNode> exprTerm = nullptr;

		eatToken();
		exprTerm = term(depth + 1);
		if (exprTerm == nullptr)
			throw ParserException("expected term");

		node = std::make_unique<BinaryOp>(token, node, exprTerm);
	}
	return node;
}

std::unique_ptr<ASTNode> Parser::expectExpr()
{
	std::unique_ptr<ASTNode> exprRoot;

	exprRoot = expr(0);
	if (exprRoot == nullptr)
		throw ParserException("expected expr");

	return exprRoot;
}

std::unique_ptr<BinaryOp> Parser::poly()
{
	std::unique_ptr<ASTNode> left, right;

	left = expectExpr();
	Token token = m_currentToken;
	if (!acceptToken(Token::Type::OP_EQUALITY))
		throw ParserException("expected equality");

	right = expectExpr();
	if (!acceptToken(Token::Type::END))
		throw ParserException("no more factor expected");

	return std::make_unique<BinaryOp>(token, left, right);
}

void Parser::printError(ParserException &e) const
{
	std::cerr << "\33[37;1msyntax:\33[0m \33[31;1merror:\33[0m ";
	if (m_lexer.formula().empty())
		std::cerr << "no input" << std::endl;
	else
	{
		std::string::size_type offset = m_lexer.offset() - m_currentToken.lexeme().length();

		if (m_currentToken.isType(Token::Type::END))
			offset += 1;

		std::cerr << "< \33[37;1m" << m_currentToken.lexeme() << "\33[0m > " << e.what() << std::endl;
		std::cerr
			<< " " << m_lexer.formula().substr(0, offset)
			<< "\33[31;1m" << m_currentToken.lexeme() << "\33[0m"
			<< m_lexer.formula().substr(m_lexer.offset())
			<< std::endl;
		std::cerr
			<< " " << std::string(offset, ' ')
			<< "\33[31;1m" << "~" << std::string(m_currentToken.lexeme().length() - 1, '-') << "\33[0m"
			<< std::endl;
	}
}
