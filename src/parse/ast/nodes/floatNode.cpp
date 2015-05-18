#include "parse/ast/nodes/floatNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

FloatNode::FloatNode(float num, int index, int parent, int line, int statement, int blkDepth)
: ast::VisitableNode(index, parent, line, statement, blkDepth)
{
	this->num	= num;
	this->value = "float";
}

float FloatNode::val()
{
	return this->num;
}

void FloatNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

} // namespace ast