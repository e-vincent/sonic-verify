#include "parse/ast/bodyNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

BodyNode::BodyNode() { }
BodyNode::BodyNode(std::string symbol, int index, int parent, int line, int statement)
{
	this->value = symbol;
	this->index = index;
	this->parent  = parent;
	this->lineNum = line;
	this->statementNum = statement;
}

void BodyNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

} // namespace ast