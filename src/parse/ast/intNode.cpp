#include "parse/ast/intNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

IntNode::IntNode() { }
IntNode::IntNode(int num, int index, int parent, int line, int statement)
{
	this->num	= num;
	this->value = "int";
	this->index = index;
	this->parent  = parent;
	this->lineNum = line;
	this->statementNum = statement;
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