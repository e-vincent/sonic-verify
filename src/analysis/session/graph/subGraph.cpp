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

char* SubGraph::consumableSType()
{
	return consumableType;
}

void SubGraph::setConsumableSType()
{
	consumableType = &processType[0];
}

void SubGraph::setConsumableSType(char* type)
{
	consumableType = type;
}

void SubGraph::printType(std::map<std::pair<arcData, std::string>, std::vector<std::pair<arcData, std::string>>> arcs)
{
	analysis::TypeVisitor* visitor = new analysis::TypeVisitor();
	// std::cout << name << "\n";

	std::string type;

	for (auto node : nodes)
	{		
		node->accept(visitor);
		bool syncType = (node->toSType() == "?");
		std::vector<std::pair<std::string, std::string>> interactions;
		for (auto it = arcs.begin(); it != arcs.end(); ++it)
		{
			std::vector<std::pair<arcData, std::string>> vec = it->second;
			for (auto p : vec)
			{
				if (((name == it->first.first.block)
						&& (it->first.second == node->symbol)) ||
					(syncType && (it->first.second == node->symbol)
						&& (p.first.index == node->index)))
				{
					interactions.push_back(std::make_pair(it->first.first.block, p.first.block));
				}
			}
		}

		node->accept(visitor, processType, interactions);
		// for (auto action : interactions)
		// {
		// 	std::cout << action.first << " " << action.second << "\n";
		// }
	}

	std::cout << "SubGraph " << name 
		<< "\n has processType " << processType << "\n";

	delete visitor;
}

} // namespace graph