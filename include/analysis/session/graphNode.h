#ifndef __GRAPH_NODE_H__
#define __GRAPH_NODE_H__

#include <list>
#include <iostream>
#include <string>

namespace analysis
{

class TypeVisitor;
class GraphNode
{
private:

public:
	int index;
	int line;
	int blk;
	std::string symbol;
	std::list<std::pair<int, int>> arcs; // two arcs types??

	GraphNode();
	GraphNode(int index, int line, std::string symbol, int blk);

	virtual void accept(analysis::TypeVisitor*);
};

} // namespace analysis

#endif // __GRAPH_NODE_H__