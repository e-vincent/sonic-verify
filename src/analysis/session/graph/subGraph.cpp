#include "analysis/session/graph/subGraph.h"

namespace graph
{

SubGraph::SubGraph() 
{ 
	firstIndex = -1;
	lastIndex  = -1;
}

void SubGraph::addNode(graph::GraphNode* node)
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

graph::GraphNode* SubGraph::get(int index)
{
	graph::GraphNode* node = NULL;

	for (auto item : nodes)
	{
		if (item->index == index)
		{
			node = item;
		}
	}

	return node;
}

std::list<graph::GraphNode*> SubGraph::nodeList()
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
	return processType;
}

void SubGraph::printType(std::map<std::pair<arcData, std::string>, std::vector<std::pair<arcData, std::string>>> arcs)
{
	analysis::TypeVisitor* visitor = new analysis::TypeVisitor();
	std::cout << name << "\n";
	for (auto node : nodes)
	{
		node->accept(visitor);
		std::cout << "Node Type: " << node->toSType() << "\n";
		for (auto it = arcs.begin(); it != arcs.end(); ++it)
		{
			if (it->first.second == node->symbol)
			{
				std::cout << "Symbol in block " << it->first.first.block << "\n";
				std::vector<std::pair<arcData, std::string>> vec = it->second;
				for (auto p : vec)
				{
					std::cout << "Links with " << p.first.block << "\n";
				}
			}
		}
	}

	delete visitor;
}

} // namespace graph