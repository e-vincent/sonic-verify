#ifndef __PLANNER_H__
#define __PLANNER_H__

#include <iostream>
#include <stack>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/directed_graph.hpp"

#include "rice/Array.hpp"

#include "main.h"

#include "analysis/session/graph/nodes/nodes.h"
#include "parse/ast/nodeTree.h"
#include "parse/treeIterator.h"

namespace analysis
{

class Planner
{
private:
	int currIndex;

public:
	//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, analysis::GraphNode> SubGraph;
	//typedef boost::graph_traits<SubGraph>::vertex_descriptor sg_vertex_t;
	//typedef boost::graph_traits<SubGraph>::edge_descriptor sg_arc_t;

	// Sub Graph typedefs
	struct sg_vertex_info
	{
		int index;
		analysis::GraphNode* node;
	};

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, sg_vertex_info> SubGraph;
	typedef boost::graph_traits<SubGraph>::vertex_descriptor sg_vertex;
	typedef boost::graph_traits<SubGraph>::vertex_iterator sg_vertex_iter;

	// Graph typedefs
	typedef boost::property<boost::vertex_name_t, SubGraph> GraphVertexProperty;
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, SubGraph> Graph;
	typedef boost::graph_traits<Graph>::vertex_descriptor g_vertex;


	typedef boost::graph_traits<Graph>::vertex_iterator g_vertex_iter;

	Graph graph;

	Planner();
	~Planner();

	void setUp();

	analysis::CueNode* makeCue(int line, std::string symbol, int blk);
	analysis::SyncNode* makeSync(int line, std::string symbol, int blk);

	void makeGraph(ast::NodeTree* tree);
	void makeSubGraph(std::stack<analysis::GraphNode*>& symbols);

	int getIndex();
	void updateIndex();
};

} // namespace analysis

#endif // __PLANNER_H__