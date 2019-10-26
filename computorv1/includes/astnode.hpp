#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>
#include "token.hpp"
#include "exprformula.hpp"

class ASTNode
{
public:
	explicit ASTNode(Token token);

	virtual ~ASTNode() = default;

	virtual void print(std::ostream &os, std::string::size_type depth = 0) const = 0;

	virtual ExprFormula compute() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const ASTNode &node);

protected:
	Token m_token;
};

#endif // ASTNODE_HPP
