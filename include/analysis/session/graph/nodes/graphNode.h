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

	GraphNode();
	GraphNode(int index, int line, std::string symbol, int blk);
};

} // namespace analysis

#endif // __GRAPH_NODE_H__