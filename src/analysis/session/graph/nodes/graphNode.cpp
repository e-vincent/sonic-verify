#include "analysis/session/graph/nodes/graphNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace graph
{

GraphNode::GraphNode() { }
GraphNode::GraphNode(int index, int line, std::string symbol)
{
	this->index  = index;
	this->line 	 = line;
	this->symbol = symbol;
}

void GraphNode::setSType(std::string type)
{
	stype = type;
}

void GraphNode::appendSType(std::string str)
{
	stype.append(str);
}

std::string GraphNode::toSType()
{
	return stype;
}

} // namespace graph