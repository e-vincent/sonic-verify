#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

#include <boost/tokenizer.hpp>

#include "analysis/session/graph/nodes/nodes.h"
#include "analysis/session/graph/subGraph.h"

namespace graph
{

class Graph
{
typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

private:
	std::vector<std::pair<arcData, std::string>> syncStore;
	std::list<graph::SubGraph*> blocks;
	std::map<std::pair<arcData, std::string>, std::vector<std::pair<arcData, std::string>>> arcs; 	// one to many map
	std::string global;
	int nodeCount;

public:
	Graph();
	~Graph();

	void printArcs();
	void addBlock(graph::SubGraph* sub);
	
	void startArc(graph::CueNode* cue, int block);
	void addToArc(graph::SyncNode* sync, int block);

	int size();
	void setNodeCount(int count);

	void printTypes();
	void printGlobal();
	void buildGlobalType();
	void parseBlocks(std::vector<std::list<graph::GraphNode*>::iterator>& node_store,
			std::vector<std::list<graph::GraphNode*>::iterator>& node_ends,
			std::vector<std::string>& types, size_t& counter);

	void printSubType(int block);
	void appendGlobal(std::string type);
	std::string globalType();

	int blockCount();
	bool dual(char one, char two);
	void resolveTypes(std::string str, std::vector<std::string>& types, std::string type, int offset);
};


} // namespace analysis

#endif // __GRAPH_H__