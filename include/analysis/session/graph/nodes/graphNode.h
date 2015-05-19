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
	std::string stype;

public:
	int index;
	int line;
	std::string symbol;

	GraphNode();
	GraphNode(int index, int line, std::string symbol);

	virtual void setSType(std::string type);
	virtual void appendSType(std::string str);
	virtual std::string toSType();
};

} // namespace analysis

#endif // __GRAPH_NODE_H__