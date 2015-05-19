#ifndef __SUBGRAPH_H__
#define __SUBGRAPH_H__

#include <iostream>
#include <string>
#include <list>
#include <map>

#include "analysis/session/graph/nodes/graphNode.h"

namespace analysis
{

class SubGraph
{
private:
	int firstIndex;
	int lastIndex;
	std::list<analysis::GraphNode*> nodes;
	std::map<int, int> arcs;

public:
	SubGraph();

	void addNode(analysis::GraphNode* node);
	void addArc(int from, int to);
	void setFirst(int index);
	void setLast(int index);

	analysis::GraphNode* get(int index);
	std::list<analysis::GraphNode*> nodeList();
	std::map<int, int> arcList();
	bool inrange(int index);

	std::string sType();
};

} // namespace analysis

#endif // __SUBGRAPH_H__