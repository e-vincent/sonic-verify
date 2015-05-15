#include "parse/ast/symNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

SymNode::SymNode(std::string symbol, int index, int parent, int line, int statement, int blkDepth)
: ast::VisitableNode(index, parent, line, statement, blkDepth)
{
	this->value   = "sym";
	this->symbol  = symbol;
}

void SymNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

std::string SymNode::acceptType()
{
	return sym();
}

std::string SymNode::sym()
{
	return this->symbol;
}

} // namespace ast