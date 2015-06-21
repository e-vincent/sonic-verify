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
	buildGlobalType();
	std::cout << global << "\n";
}

void Graph::buildGlobalType()
{
	std::vector<std::list<graph::GraphNode*>::iterator> node_store;
	std::vector<std::list<graph::GraphNode*>::iterator> node_ends;

	std::vector<std::string> types;

	for (auto sub : blocks)
	{
		node_store.push_back(sub->nodes.begin());
		node_ends.push_back(sub->nodes.end());
	}

	size_t counter = 0;
	while (!node_store.empty())
	{
		parseBlocks(node_store, node_ends, types, counter);
	}

	for (auto sub : blocks)
	{
		node_store.push_back(sub->nodes.begin());
		node_ends.push_back(sub->nodes.end());
	}

	// run once more with start of types to catch end syncs
	parseBlocks(node_store, node_ends, types, counter);

	// shave last char from type
	// then print
	global.erase(global.length() - 1);
}

void Graph::parseBlocks(std::vector<std::list<graph::GraphNode*>::iterator>& node_store,
		std::vector<std::list<graph::GraphNode*>::iterator>& node_ends,
		std::vector<std::string>& types, size_t& counter)
{

		for (size_t i = 0; i < node_store.size(); ++i)
		{
			std::list<graph::GraphNode*>::iterator list = node_store[i];
			std::list<graph::GraphNode*>::iterator ends = node_ends[i];
			
			// store this block in a temp
			std::vector<std::string> temp;

			// 'type blocks' denoted by passage of time
			// or reaching end of list
			// or temporarily halted by blocking sync call
			while(((*list)->toSType() != "time") && (list != ends)
					&& ((*list)->toSType().back() != '?')) 
			{
				std::cout << (*list)->toSType() << "\n";
				temp.push_back((*list)->toSType());
				++list;
			}

			if ((*list)->toSType().back() == '?')
			{
				for (auto type : types)
				{
					if (type == (*list)->toSType())
					{
						//set type to untypeable
						break;
					}
				}

				std::cout << (*list)->toSType() << "\n";
				temp.push_back((*list)->toSType());
				++list;
			}

			int offset = 0;
			// do any current tokens dual our stored set?
			for (auto str : temp)
			{
				for (auto type : types)
				{
					// check they work with the same message
					// check they are dual types
					if (str.front() == type.front() 
							&& dual(str.back(), type.back()))
					{
						resolveTypes(str, types, type, offset);
					}

					++offset;
				}
			}

			// once types have been resolved, push temp
			for (auto str : temp)
			{
				types.push_back(str);
			}

			if ((*list)->toSType() == "time")
			{
				++list;
			}

			// if the current list ended, clear it from our vector
			// otherwise, update the current index for next run
			if (list == ends)
			{
				node_store.erase(node_store.begin());
				node_ends.erase(node_ends.begin());
			}
			else
			{
				node_store[i] = list;
			}

			++list;
		}

		std::cout << "Out of For\n";
		++counter;

		if (counter == blocks.size() && !types.empty())
		{
			types.clear();
		}
		// reset at each time progression
		// types.clear();
	
}

void Graph::printSubType(int block)
{
	std::cout << "Print block " << block << "\n";
}

void Graph::appendGlobal(std::string type)
{
	global.append(type);
}

std::string Graph::globalType()
{
	return global;
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

void Graph::resolveTypes(std::string str, std::vector<std::string>& types, 
		std::string type, int offset)
{
	std::string orDlim  = "||"; // sync
	std::string andDlim = "&&"; // cue
	std::string search;
	size_t found;

	boost::char_separator<char> sep(":()");
	tokenizer tok(str, sep);
	tokenizer::iterator tok_iter = tok.begin();

	for (++tok_iter; tok_iter != tok.end(); ++tok_iter)
	{
		search = *tok_iter;
		found  = search.find(orDlim);
		if (found != std::string::npos)
		{
			std::cout << "or type\n";
		}

		found  = search.find(andDlim);
		if (found != std::string::npos)
		{
			std::cout << "and type\n";
		}

		found  = type.find(search);
		if(found != std::string::npos)
		{
			std::cout << "new relation\n";
			boost::char_separator<char> sep("P");
			tokenizer token(search, sep);

			std::string result = "";
			for (tokenizer::iterator tok_it = token.begin(); tok_it != token.end(); ++tok_it)
			{
				std::cout << *tok_it << "\n";
				result.append("P").append(*tok_it);
				if (tok_it == token.begin())
				{
					result.append("->");
				}
			}

			result.append(".");
			appendGlobal(result);
			types.erase(types.begin() + offset);
		}
	}
}

void Graph::setDataExists(bool state)
{
	data = state;
}

bool Graph::dataExists()
{
	return data;
}

} // namespace graph