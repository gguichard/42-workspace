#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <string>
#include "token.hpp"
#include "astnode.hpp"

class Number : public ASTNode
{
public:
	explicit Number(Token token);

	void print(std::ostream &os, std::string::size_type depth = 0) const;

	ExprFormula compute() const;
};

#endif // NUMBER_HPP
