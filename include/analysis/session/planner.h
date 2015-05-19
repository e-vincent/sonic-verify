#ifndef __PLANNER_H__
#define __PLANNER_H__

#include <iostream>
#include <stack>

#include "rice/Array.hpp"

#include "main.h"

#include "analysis/session/graph/nodes/nodes.h"
#include "analysis/session/graph/graph.h"
#include "parse/ast/nodeTree.h"
#include "parse/treeIterator.h"

namespace analysis
{

class Planner
{
private:
	int currIndex;

public:
	analysis::Graph* graph;

	Planner();
	~Planner();

	void setUp();

	analysis::CueNode* makeCue(int line, std::string symbol);
	analysis::SyncNode* makeSync(int line, std::string symbol);

	void makeGraph(ast::NodeTree* tree);
	void makeSubGraph(std::stack<analysis::GraphNode*>& symbols);

	int getIndex();
	void updateIndex();
};

} // namespace analysis

#endif // __PLANNER_H__