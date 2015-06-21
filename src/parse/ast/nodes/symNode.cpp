#include "parse/ast/nodes/symNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

SymNode::SymNode(std::string symbol, int index, int parent, int line, int statement, int blkDepth, int blkIndex)
: ast::VisitableNode(index, parent, line, statement, blkDepth, blkIndex)
{
	this->value   = "sym";
	this->symbol  = symbol;
}

void SymNode::accept(analysis::PTrace* trace, VTimeVisitor* v)
{
	v->visit(trace, this);
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