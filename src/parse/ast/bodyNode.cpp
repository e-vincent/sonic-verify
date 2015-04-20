#include "parse/ast/bodyNode.h"
#include "parse/ast/iVisitor.h"

namespace ast
{

BodyNode::BodyNode() { }
BodyNode::BodyNode(std::string symbol, int index, int parent)
{
	this->value = symbol;
	this->index = index;	
	this->parent = parent;
}

void BodyNode::accept(IVisitor v)
{
	v.visit(this);
}

} // namespace ast