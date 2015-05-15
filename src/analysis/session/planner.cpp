#include "analysis/session/planner.h"

namespace analysis
{

Planner::Planner()
{
	currIndex = 0;
	std::cout << "New Party Planner\n";
}

Planner::~Planner()
{
	
}

void Planner::setUp()
{
	makeGraph(Builder::tree);
}

analysis::CueNode* Planner::makeCue(int line, std::string symbol, int blk)
{
	std::cout << "MAKE CUE\n";
	std::cout << line << " " << symbol << " " << blk << "\n";
	return new analysis::CueNode(getIndex(), line, symbol, blk);
}

analysis::SyncNode* Planner::makeSync(int line, std::string symbol, int blk)
{
	std::cout << "MAKE SYNC\n";
	return new analysis::SyncNode(getIndex(), line, symbol, blk);
}


void Planner::makeGraph(ast::NodeTree* tree)
{
// 	SubGraph sub;
// 	boost::property_map<SubGraph, boost::vertex_name_t>::type
//   		city_name = get(boost::vertex_name, sub);
// //	sg_vertex_t v = boost::add_vertex(sub);
// 	sg_vertex v = boost::add_vertex(sub);


// 	city_name[v] = "London";

// 	std::pair<sg_vertex_iter, sg_vertex_iter> vp;
// 	for (vp = vertices(sub); vp.first != vp.second; ++vp.first)
// 	{
// 		std::cout << city_name[*vp.first] << "\n";
// 	}
// 	//return sub;

// 	boost::property_map<Graph, boost::vertex_name_t>::type
// 		subGraph = get(boost::vertex_name, graph);
// 	g_vertex g_v = boost::add_vertex(graph);
// 	subGraph[g_v] = sub;

// 	std::pair<g_vertex_iter, g_vertex_iter> it;
// 	for (it = vertices(graph); it.first != it.second; ++it.first)
// 	{
// 		//std::cout << node[*it.first] << "\n";
// 		for (vp = vertices(subGraph[*it.first]); vp.first != vp.second; ++vp.first)
// 		{
// 			std::cout << "RARAAWR" << "\n";
// 			std::cout << city_name[*vp.first] << "\n";
// 		}
// 	}

	int currBlk = 0;

	std::stack<analysis::GraphNode*> symbols;

	ast::TreeIterator start = tree->begin();
	ast::TreeIterator end   = tree->end();
	// first pass - setup VTs
	for (ast::TreeIterator it = start; it != end; ++it)
	{
		ast::VisitableNode* curr = &(*it);
		if (curr->value == "block")
		{
			std::cout << "New Block" << "\n";
			if (!symbols.empty())
			{
				makeSubGraph(symbols);
			}
			++currBlk;
		}

		analysis::GraphNode* node = NULL;
		if (curr->value == "cue")
		{
			ast::VisitableNode* next = &(*(++it));
			node = makeCue(curr->line(), next->acceptType(), currBlk);
			std::cout << "Found C/S Line " << curr->line() << "\n"; 
		} 
		
		if (curr->value == "sync")
		{
			ast::VisitableNode* next = &(*(++it));
			node = makeSync(curr->line(), next->acceptType(), currBlk);
			std::cout << "Found C/S Line " << curr->line() << "\n"; 
		}

		if (node)
		{
			symbols.push(node);
			updateIndex();
		}
	}

	int index = graph[0][0].index;
	std::cout << "first index " << index << "\n";

	std::cout << graph[0][1].index << "\n";
	std::cout << graph[1][0].index << "\n";
	std::cout << graph[2][1].index << "\n";
	std::cout << graph[2][2].index << "\n";

	analysis::GraphNode* node = graph[0][0].node;
	std::cout << "node " << node->symbol << "\n";
	//std::cout << "top graph size " << graph.size() << "\n";
//	analysis::Planner::sg_vertex_info subG = graph[0];
	// std::pair<sg_vertex_iter, sg_vertex_iter> vp;
	// std::pair<g_vertex_iter, g_vertex_iter> it;
	// for (it = vertices(graph); it.first != it.second; ++it.first)
	// {
	// 	//std::cout << node[*it.first] << "\n";
	// 	for (vp = vertices(subGraph[*it.first]); vp.first != vp.second; ++vp.first)
	// 	{
	// 		std::cout << "RARAAWR" << "\n";
	// 		std::cout << (*vp.first). << "\n";
	// 	}
	// }
}

void Planner::makeSubGraph(std::stack<analysis::GraphNode*>& symbols)
{
	analysis::GraphNode* node;
	SubGraph sub;
	// boost::property_map<SubGraph, analysis>::type
 //  		sg_node = get(boost::vertex_name, sub);

  	sg_vertex sg_v;


	while (!symbols.empty())
	{
		sg_v = boost::add_vertex(sub);
		sub[sg_v].index = getIndex();
		sub[sg_v].node = *(&symbols.top());
		node = *(&symbols.top());
//		&symbols.pop();
		symbols.pop();
		//analysis::GraphNode* node = &(symbols.pop());
		std::cout << "Symbol loop: " << node->symbol << "\n";
	}

	g_vertex g_v = boost::add_vertex(graph);
	graph[g_v] = sub;

	//for (auto node : nodes)
	// for (int i = 0; i < nodes.size(); ++i)
	// {
	// 	analysis::GraphNode node = nodes[i];
	// 	std::cout << node->line() << "\n";
	// }

//	for (auto it = arr.begin(); it != arr.end(); ++it)
	// for (auto rar : strs[0])
	// {
	// 	std::cout << rar << "\n";
	// }

	// for (auto str : strs)
	// {
	// 	std::cout << str << "\n";
	// 	// ["1", "m", "3", "4"]

	// 	// ptr = (*it)

	// 	// is ptr[1] == "m"  ?



	// //	std::cout << decltype(it->value())("") << "\n";
	// }
}

int Planner::getIndex()
{
	return currIndex;
}

void Planner::updateIndex()
{
	++currIndex;
}

} // namespace analysis