#ifndef BINARYOP_HPP
#define BINARYOP_HPP

#include <memory>
#include <string>
#include "token.hpp"
#include "astnode.hpp"
#include "exprformula.hpp"

class BinaryOp : public ASTNode
{
public:
	explicit BinaryOp(Token token, std::unique_ptr<ASTNode> &left, std::unique_ptr<ASTNode> &right);

	void print(std::ostream &os, std::string::size_type depth = 0) const;

	ASTNode &left() const;
	ASTNode &right() const;
	ExprFormula compute() const;

private:
	std::unique_ptr<ASTNode> m_left;
	std::unique_ptr<ASTNode> m_right;
};

#endif // BINARYOP_HPP
