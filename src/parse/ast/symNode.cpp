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

void SymNode::accept(analysis::PTrace* trace, VTimeVisitor* v)
{
	v->visit(trace, this);
}

std::string SymNode::sym()
{
	return this->symbol;
}

} // namespace ast