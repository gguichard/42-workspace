#include <memory>
#include <string>
#include "binaryop.hpp"
#include "astnode.hpp"
#include "token.hpp"
#include "exprformula.hpp"

BinaryOp::BinaryOp(Token token, std::unique_ptr<ASTNode> &left, std::unique_ptr<ASTNode> &right)
	: ASTNode(token), m_left(std::move(left)), m_right(std::move(right))
{
}

void BinaryOp::print(std::ostream &os, std::string::size_type depth) const
{
	m_left->print(os, depth + 1);
	os << std::string(depth, '\t') << m_token << std::endl;
	m_right->print(os, depth + 1);
}

ASTNode &BinaryOp::left() const
{
	return *m_left;
}

ASTNode &BinaryOp::right() const
{
	return *m_right;
}

ExprFormula BinaryOp::compute() const
{
	switch (m_token.type())
	{
	case Token::Type::OP_PLUS:
		return m_left->compute() + m_right->compute();
	case Token::Type::OP_MINUS:
		return m_left->compute() - m_right->compute();
	case Token::Type::OP_MUL:
		return m_left->compute() * m_right->compute();
	case Token::Type::OP_DIV:
		return m_left->compute() / m_right->compute();
	case Token::Type::OP_POW:
		return m_left->compute() ^ m_right->compute();
	default:
		return ExprFormula();
	}
}
