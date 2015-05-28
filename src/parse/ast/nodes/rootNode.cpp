#include "parse/ast/nodes/rootNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

RootNode::RootNode(std::string root)
{
	this->value = root;
	this->index = 0;
	this->parent  = -1;
	this->lineNum = -1;
	this->statementNum = -1;
}

void RootNode::accept(analysis::PTrace* trace, ast::VTimeVisitor* v)
{
	v->visit(trace, this);
}

} // namespace ast