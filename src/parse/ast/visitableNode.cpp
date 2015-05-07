#include "parse/ast/visitableNode.h"

namespace ast
{

int VisitableNode::line()
{
	return this->lineNum;
}

int VisitableNode::statement()
{
	return this->statementNum;
}

} // namespace ast
