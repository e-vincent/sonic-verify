#ifndef __CUE_NODE_H__
#define __CUE_NODE_H__

#include <string>

#include "analysis/session/graph/nodes/graphNode.h"

namespace graph
{

class CueNode : public GraphNode
{
public:
	CueNode(int index, int line, std::string symbol);

	virtual void accept(analysis::TypeVisitor* v);
	virtual void accept(analysis::TypeVisitor* v, std::string& type, std::vector<std::pair<std::string, std::string>> interactions);
};

} // namespace graph

#endif // __CUE_NODE_H__