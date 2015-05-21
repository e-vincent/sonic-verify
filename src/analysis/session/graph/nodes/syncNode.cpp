#include "analysis/session/graph/nodes/syncNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace graph
{

SyncNode::SyncNode(int index, int line, std::string symbol)
: GraphNode(index, line, symbol) { }

void SyncNode::accept(analysis::TypeVisitor* v)
{
	v->visit(this);
}

} // namespace graph