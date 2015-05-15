#include "analysis/session/graphNode.h"
#include "analysis/session/typeVisitor.h"

namespace analysis
{

GraphNode::GraphNode() { }
GraphNode::GraphNode(int index, int line, std::string symbol, int blk)
{
	this->index  = index;
	this->line 	 = line;
	this->symbol = symbol;
	this->blk 	 = blk;
}

void GraphNode::accept(TypeVisitor* v)
{
	v->visit(this);
}

} // namespace analysis