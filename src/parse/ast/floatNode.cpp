#include "parse/ast/floatNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

FloatNode::FloatNode() { }
FloatNode::FloatNode(float num, int index, int parent, int line, int statement)
{
	this->num	= num;
	this->value = "float";
	this->index = index;
	this->parent  = parent;
	this->lineNum = line;
	this->statementNum = statement;
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