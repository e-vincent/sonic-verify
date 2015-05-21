#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "analysis/session/graph/nodes/nodes.h"
#include "analysis/session/graph/subGraph.h"

namespace graph
{

class Graph
{
private:
	std::vector<std::pair<arcData, std::string>> syncStore;
	std::list<graph::SubGraph*> blocks;
	std::map<std::pair<arcData, std::string>, std::vector<std::pair<arcData, std::string>>> arcs; 	// one to many map

public:
	Graph();
	~Graph();

	void printArcs();
	void addBlock(graph::SubGraph* sub);
	
	void startArc(graph::CueNode* cue, int block);
	void addToArc(graph::SyncNode* sync, int block);

	void printTypes();
	void printSubType(int block);
	int blockCount();
};


} // namespace analysis

#endif // __GRAPH_H__