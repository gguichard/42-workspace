#ifndef UNARYOP_HPP
#define UNARYOP_HPP

#include <memory>
#include <string>
#include "astnode.hpp"
#include "token.hpp"
#include "exprformula.hpp"

class UnaryOp : public ASTNode
{
public:
	explicit UnaryOp(Token token, std::unique_ptr<ASTNode> &node);

	void print(std::ostream &os, std::string::size_type depth = 0) const;

	ExprFormula compute() const;

private:
	std::unique_ptr<ASTNode> m_node;
};

#endif // UNARYOP_HPP
