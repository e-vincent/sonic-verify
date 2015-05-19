#include "analysis/session/graph/nodes/syncNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

SyncNode::SyncNode(int index, int line, std::string symbol)
: GraphNode(index, line, symbol) { }

void SyncNode::accept(TypeVisitor* v)
{
	v->visit(this);
}

} // namespace analysis