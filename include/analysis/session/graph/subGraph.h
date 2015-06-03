#ifndef __SUBGRAPH_H__
#define __SUBGRAPH_H__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>

#include "analysis/session/graph/sgIterator.h"
#include "analysis/session/graph/nodes/graphNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace graph
{

struct arcData
{
	int line;
	int index;
	std::string block;

	bool operator==(const arcData &o) const {
        return (line == o.line) && (index == o.index) 
        	&& (block == o.block);
    }

    bool operator<(const arcData &o) const {
        return (line < o.line)
        	|| ((line == o.line) && (index < o.index));
    }
};

class SGIterator;

class SubGraph
{
private:
	int firstIndex;
	int lastIndex;
	std::string processType;

public:
	std::list<graph::GraphNode*> nodes;
	std::map<int, int> arcs;
	std::string name;

	SubGraph();

	SGIterator begin();
	SGIterator end();

	void addNode(graph::GraphNode* node);
	void addArc(int from, int to);
	void setFirst(int index);
	void setLast(int index);

	graph::GraphNode* get(int index);
	std::list<graph::GraphNode*> nodeList();
	std::map<int, int> arcList();
	bool inrange(int index);

	std::string sType();
	void constructType(std::map<std::pair<arcData, std::string>, std::vector<std::pair<arcData, std::string>>> arcs);
};

} // namespace graph

#endif // __SUBGRAPH_H__