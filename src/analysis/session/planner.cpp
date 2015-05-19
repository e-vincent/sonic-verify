#include "analysis/session/planner.h"

namespace analysis
{

Planner::Planner()
{
	currIndex = 0;
	graph = new Graph();
	std::cout << "New Party Planner\n";
}

Planner::~Planner()
{
	
}

void Planner::setUp()
{
	makeGraph(Builder::tree);
}

analysis::CueNode* Planner::makeCue(int line, std::string symbol)
{
	std::cout << "MAKE CUE\n";
	std::cout << line << " " << symbol << " " << "\n";
	return new analysis::CueNode(getIndex(), line, symbol);
}

analysis::SyncNode* Planner::makeSync(int line, std::string symbol)
{
	std::cout << "MAKE SYNC\n";
	return new analysis::SyncNode(getIndex(), line, symbol);
}


void Planner::makeGraph(ast::NodeTree* tree)
{
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
			node = makeCue(curr->line(), next->acceptType());
			std::cout << "Found C/S Line " << curr->line() << "\n"; 
		} 
		
		if (curr->value == "sync")
		{
			ast::VisitableNode* next = &(*(++it));
			node = makeSync(curr->line(), next->acceptType());
			std::cout << "Found C/S Line " << curr->line() << "\n"; 
		}

		if (node)
		{
			symbols.push(node);
			updateIndex();
		}
	}

}

void Planner::makeSubGraph(std::stack<analysis::GraphNode*>& symbols)
{
	analysis::GraphNode* node = NULL;
	analysis::GraphNode* prev = NULL;
	SubGraph* sub = new SubGraph();

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