#include <string>
#include "number.hpp"
#include "token.hpp"
#include "exprformula.hpp"

Number::Number(Token token) : ASTNode(token)
{
}

void Number::print(std::ostream &os, std::string::size_type depth) const
{
	os << std::string(depth, '\t') << m_token << std::endl;
}

ExprFormula Number::compute() const
{
	ExprFormula expr;

	switch (m_token.type())
	{
	case Token::Type::NUMBER:
		expr.factor(0).value += std::stod(m_token.lexeme());
		break;
	case Token::Type::VAR:
		expr.factor(1).value += 1;
		break;
	default:
		break;
	}
	return expr;
}
