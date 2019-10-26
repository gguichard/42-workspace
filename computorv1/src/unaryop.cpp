#include <memory>
#include <string>
#include "unaryop.hpp"
#include "token.hpp"
#include "exprformula.hpp"

UnaryOp::UnaryOp(Token token, std::unique_ptr<ASTNode> &node) : ASTNode(token), m_node(std::move(node))
{
}

void UnaryOp::print(std::ostream &os, std::string::size_type depth) const
{
	os << std::string(depth, '\t') << m_token << std::endl;
	m_node->print(os, depth + 1);
}

ExprFormula UnaryOp::compute() const
{
	switch (m_token.type())
	{
	default:
	case Token::Type::OP_PLUS:
		return m_node->compute();
	case Token::Type::OP_MINUS:
		return -m_node->compute();
	}
}
