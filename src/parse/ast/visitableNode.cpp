#include "parse/ast/visitableNode.h"

namespace ast
{

// VisitableNode::operator IntNode() const
// {
// 	// this is trying to upcast VisitableNode
// 	// given that we're assuming the data set we've 
// 	// been given would actually be an IntNode...
// 	return new ast::IntNode();
// }

int VisitableNode::line()
{
	return this->lineNum;
}

int VisitableNode::statement()
{
	return this->statementNum;
}

} // namespace ast
