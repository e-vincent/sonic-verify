#include "parse/ast/nodes/sendNode.h"
#include "parse/ast/vTimeVisitor.h"
#include "parse/ast/basicVisitor.h"

namespace ast
{

SendNode::SendNode(int index, int parent, int line, int statement, int blkDepth, int blkIndex)
: ast::VisitableNode(index, parent, line, statement, blkDepth, blkIndex)
{
	this->value = "send";
}

void SendNode::accept(analysis::PTrace* trace, VTimeVisitor* v)
{
	v->visit(trace, this);
}

void SendNode::accept(BasicVisitor* v, std::string sym)
{
	v->visit(this);
	setFuncName(sym);
	setType("function");
}

void SendNode::setType(std::string s)
{
	this->sendType = s;
}

void SendNode::setFuncName(std::string s)
{
	this->funcName = s;
}

std::string SendNode::type()
{
	return this->sendType;
}

std::string SendNode::func()
{
	return this->funcName;
}

} // namespace ast