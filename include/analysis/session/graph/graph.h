#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string>
#include <map>
#include <list>

#include "analysis/session/graph/subGraph.h"

namespace analysis
{

class Graph
{
private:
	std::list<analysis::SubGraph*> blocks;
	std::map<int, int> arcs;

public:
	Graph();
	~Graph();

	void addBlock(SubGraph* sub);
	void addArc(int from, int to);

	int blockCount();
};


} // namespace analysis

#endif // __GRAPH_H__