#include "analysis/session/graph/nodes/graphNode.h"
#include "analysis/session/graph/typeVisitor.h"

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

} // namespace analysis