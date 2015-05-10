#include "parse/ast/visitableNode.h"

namespace ast
{

VisitableNode::VisitableNode() { }
VisitableNode::VisitableNode(int index, int parent, int line, int statement, int blkDepth)
{
	this->index = index;
	this->parent = parent;
	this->lineNum = line;
	this->statementNum = statement;
	this->blkDepth = blkDepth;
}

void VisitableNode::accept(BasicVisitor*, std::string)
{
	// stub
}

int VisitableNode::line()
{
	return this->lineNum;
}

int VisitableNode::statement()
{
	return this->statementNum;
}

int VisitableNode::blockDepth()
{
	return this->blkDepth;
}

} // namespace ast
