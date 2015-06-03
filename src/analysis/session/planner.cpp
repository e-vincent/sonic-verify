#include "analysis/session/planner.h"

namespace analysis
{

Planner::Planner()
{
	currIndex = 0;
	subCount  = 0;
	graph = new graph::Graph();
}

Planner::~Planner()
{
	
}

void Planner::setUp()
{
	makeGraph(Builder::tree);

	// printing test
	std::cout << "\n\n === Arc Results === \n";
	graph->printArcs();
	graph->printTypes();
	graph->printGlobal();
}

graph::CueNode* Planner::makeCue(int line, std::string symbol)
{
	return new graph::CueNode(getIndex(), line, symbol);
}

graph::SyncNode* Planner::makeSync(int line, std::string symbol)
{
	return new graph::SyncNode(getIndex(), line, symbol);
}


void Planner::makeGraph(ast::NodeTree* tree)
{
	int currBlk = 0;

	std::stack<graph::GraphNode*> symbols;

	ast::TreeIterator start = tree->begin();
	ast::TreeIterator end   = tree->end();
	// first pass - setup VTs
	for (ast::TreeIterator it = start; it != end; ++it)
	{
		ast::VisitableNode* curr = &(*it);
		if (curr->value == "block")
		{
			if (!symbols.empty())
			{
				makeSubGraph(symbols);
			}
			++currBlk;
		}

		//bool timeProgression = false;
		graph::GraphNode* node = NULL;
		if (curr->value == "cue")
		{
			ast::VisitableNode* next = &(*(++it));
			graph::CueNode* cueNode  = makeCue(curr->line(), next->acceptType());
			graph->startArc(cueNode, subCount);
			node = cueNode;
		} 
		else if (curr->value == "sync")
		{
			ast::VisitableNode* next  = &(*(++it));
			graph::SyncNode* syncNode = makeSync(curr->line(), next->acceptType());
			graph->addToArc(syncNode, subCount);
			node = syncNode;
		} 
		else if (curr->value == "sleep")
		{
			std::cout << "Found Sleep\n";
		}

		if (node)
		{
			symbols.push(node);
			updateIndex();
		}
	}

	// catch last block
	makeSubGraph(symbols);
	graph->setNodeCount(getIndex());
}

void Planner::makeSubGraph(std::stack<graph::GraphNode*>& symbols)
{
	graph::GraphNode* node = NULL;
	graph::GraphNode* prev = NULL;
	graph::SubGraph* sub = new graph::SubGraph();
	sub->name.append("P").append(std::to_string(subCount++));

	bool flag = true;
	while (!symbols.empty())
	{
		node = *(&symbols.top());
		if (flag)
		{
			sub->setFirst(node->index);
			flag = false;
		}

		sub->addNode(node);
		if (prev)
		{
			sub->addArc(prev->index, node->index);
		}

		symbols.pop();
	}

	sub->setLast(node->index);
	graph->addBlock(sub);
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