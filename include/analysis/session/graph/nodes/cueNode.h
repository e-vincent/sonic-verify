#ifndef __CUE_NODE_H__
#define __CUE_NODE_H__

#include <string>

#include "analysis/session/graph/nodes/graphNode.h"

namespace analysis
{

class CueNode : public GraphNode
{
public:
	CueNode(int index, int line, std::string symbol);

	virtual void accept(TypeVisitor* v);
};

} // namespace analysis

#endif // __CUE_NODE_H__