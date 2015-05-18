#include "parse/ast/nodes/intNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

IntNode::IntNode(int num, int index, int parent, int line, int statement, int blkDepth)
: ast::VisitableNode(index, parent, line, statement, blkDepth)
{
	this->num	= num;
	this->value = "int";
}

int IntNode::val()
{
	return this->num;
}

void IntNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

} // namespace ast