#ifndef __PLANNER_H__
#define __PLANNER_H__

#include <iostream>
#include <stack>

#include "main.h"

#include "analysis/session/graph/nodes/nodes.h"
#include "analysis/session/graph/graph.h"
#include "parse/ast/nodeTree.h"
#include "parse/ast/treeIterator.h"

namespace analysis
{

class Planner
{
private:
	int currIndex;
	int subCount;

public:
	graph::Graph* graph;

	Planner();
	~Planner();

	void setUp();
	void printDetails();

	graph::CueNode* makeCue(int line, std::string symbol);
	graph::SyncNode* makeSync(int line, std::string symbol);

	void makeGraph(ast::NodeTree* tree);
	void makeSubGraph(std::stack<graph::GraphNode*>& symbols);

	int getIndex();
	void updateIndex();
};

} // namespace analysis

#endif // __PLANNER_H__