#include "parse/ast/sendNode.h"
#include "parse/ast/vTimeVisitor.h"
#include "parse/ast/basicVisitor.h"

namespace ast
{

SendNode::SendNode() { }
SendNode::SendNode(int index, int parent, int line, int statement)
{
	this->value = "send";
	this->index = index;
	this->parent  = parent;
	this->lineNum = line;
	this->statementNum = statement;
}

void SendNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

void SendNode::accept(BasicVisitor* v, std::string sym)
{
	v->visit(this);
	setFuncName(sym);
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