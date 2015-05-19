#include "analysis/session/graph/subGraph.h"

namespace analysis
{

SubGraph::SubGraph() 
{ 
	firstIndex = -1;
	lastIndex  = -1;
}

void SubGraph::addNode(analysis::GraphNode* node)
{
	nodes.push_front(node);
}

void SubGraph::addArc(int from, int to)
{
	arcs.insert(std::pair<int, int>(from, to));
}

void SubGraph::setFirst(int index)
{
	if (firstIndex == -1)
	{
		firstIndex = index;
	}
}

void SubGraph::setLast(int index)
{
	if (lastIndex == -1)
	{
		lastIndex = index;
	}
}

analysis::GraphNode* SubGraph::get(int index)
{
	analysis::GraphNode* node = NULL;

	for (auto item : nodes)
	{
		if (item->index == index)
		{
			node = item;
		}
	}

	return node;
}

std::list<analysis::GraphNode*> SubGraph::nodeList()
{
	return nodes;
}

std::map<int, int> SubGraph::arcList()
{
	return arcs;
}

bool SubGraph::inrange(int index)
{
	return ((firstIndex < index) && (lastIndex > index));
}

std::string SubGraph::sType()
{
	return "unknown";
}

} // namespace analysis