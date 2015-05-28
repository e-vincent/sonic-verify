#ifndef __GRAPH_NODE_H__
#define __GRAPH_NODE_H__

#include <list>
#include <iostream>
#include <string>
#include <vector>

namespace analysis
{class TypeVisitor;} // namespace analysis

namespace graph
{

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

	virtual void accept(analysis::TypeVisitor*) {};
	virtual void accept(analysis::TypeVisitor*, std::string&, std::vector<std::pair<std::string, std::string>>) {};
};

} // namespace analysis

#endif // __GRAPH_NODE_H__