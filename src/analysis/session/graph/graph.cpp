#include "analysis/session/graph/graph.h"

namespace graph
{

Graph::Graph()
{

}

void Graph::printArcs()
{
	for (auto it = arcs.begin(); it != arcs.end(); ++it)
	{
		std::cout << "Cue " << it->first.first.index << " "
			<< "Block:" << it->first.first.block
			<< " " << it->first.second
			<< "\n   |_> points at " << "\n";

		std::vector<std::pair<arcData, std::string>> vec = it->second;
		for (auto p : vec)
		{
			std::cout << "       -> " << p.first.block << ": "
				<< p.first.index 
				<< " " << p.second << "\n";
		}
	}

	std::cout << " '' Unclaimed Syncs '' \n";
	for (auto p : syncStore)
	{
		std::cout << "       = " << p.first.index << " " << p.second << "\n";
	}
}

void Graph::addBlock(graph::SubGraph* sub)
{
	blocks.push_back(sub);
}

void Graph::startArc(graph::CueNode* cue, int block)
{
	std::vector<std::pair<arcData, std::string>> to;
	arcData newData;
	newData.line  = cue->line;
	newData.index = cue->index;
	newData.block.append("P").append(std::to_string(block));
	std::pair<arcData, std::string> from(newData, cue->symbol);
	
	std::vector<int> offsets;
	int offset = 0;

	// any valid syncs in storage?
	for (auto p : syncStore)
	{
		if (p.second == cue->symbol)
		{
			to.push_back(p);
			offsets.push_back(offset); // store offsets to erase after loop
		}
		++offset;
	}

	for (int offset : offsets)
	{
		syncStore.erase(syncStore.begin() + offset);
	}

	// has this symbol occured on another line?
	//   - all symbols should result in the same list
	//     so we break on first find
	for (auto it = arcs.begin(); it != arcs.end(); ++it)
	{
		if (it->first.second == cue->symbol)
		{
			to = it->second;
			break;
		}
	}

	arcs.insert(std::make_pair(from, to));
}

void Graph::addToArc(graph::SyncNode* sync, int block)
{
	arcData newData;
	newData.line  = sync->line;
	newData.index = sync->index;
	newData.block.append("P").append(std::to_string(block));

	bool stored = false;
	for (auto it = arcs.begin(); it != arcs.end(); ++it)
	{
		// find correct reference 
		//    - no break since there may be multiple cue symbols
		if (it->first.second == sync->symbol)
		{
			it->second.push_back(std::make_pair(newData, sync->symbol));
			stored = true;
		}
	}

	// need to remember the symbol and line for when cue occurs
	if (!stored)
	{
		syncStore.push_back(std::make_pair(newData, sync->symbol));
	}
}

int Graph::size()
{
	return nodeCount;
}

void Graph::setNodeCount(int count)
{
	nodeCount = count;
}

void Graph::printTypes()
{
	for (auto sub : blocks)
	{
		sub->constructType(arcs);
		std::cout << "SubGraph " << sub->name 
			<< "\n has processType " << sub->sType() << "\n";
	}
}

void Graph::printGlobal()
{
	std::vector<graph::SGIterator> it_store;
	std::vector<graph::SGIterator> end_store;
	std::cout << "Node Count: " << size() << "\n";

	for (auto sub : blocks)
	{
		it_store.push_back(sub->begin());
		end_store.push_back(sub->end());
	}

	for (int i = 0; i < (int)it_store.size(); ++i)
	{
		auto it  = it_store[i];
		auto end = end_store[i];

		while(it != end)
		{
			std::cout << (&(*it))->toSType() << "\n";
			++it;
		}
	}

	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	// boost::char_separator<char> sep(":");
	// tokenizer tok(sub->sType(), sep);
	// for(tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
	// {

	// }		
}

void Graph::printSubType(int block)
{
	std::cout << "Print block " << block << "\n";
}

int Graph::blockCount()
{
	return blocks.size();
}

bool Graph::dual(char one, char two)
{
	return ((one == '!') && (two == '?')) 
			|| ((one == '?') && (two == '!'));
}

} // namespace graph