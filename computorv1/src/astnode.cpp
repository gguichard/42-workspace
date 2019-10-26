#include "astnode.hpp"
#include "token.hpp"

ASTNode::ASTNode(Token token) : m_token(token)
{
}

std::ostream &operator<<(std::ostream &os, const ASTNode &node)
{
	node.print(os);
	return os;
}
