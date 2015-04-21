#include "parse/ast/rootNode.h"
#include "parse/ast/iVisitor.h"

namespace ast
{

RootNode::RootNode() { }
RootNode::RootNode(std::string root)
{
	this->value = root;
	this->index = 0;
	this->parent = -1;
}

void RootNode::accept(IVisitor v)
{
	v.visit(this);
}

} // namespace ast