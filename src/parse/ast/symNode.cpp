#include "parse/ast/symNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

//SymNode::SymNode();
SymNode::SymNode(std::string symbol, int index, int parent, int line, int statement)
{
	this->value   = "sym";
	this->symbol  = symbol;
	this->index   = index;
	this->parent  = parent;
	this->lineNum = line;
	this->statementNum = statement;
}

void SymNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

std::string SymNode::sym()
{
	return this->symbol;
}

} // namespace ast