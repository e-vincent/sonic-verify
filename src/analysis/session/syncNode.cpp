#include "analysis/session/syncNode.h"
#include "analysis/session/typeVisitor.h"

namespace analysis
{

SyncNode::SyncNode(int index, int line, std::string symbol, int blk)
: GraphNode(index, line, symbol, blk) { }

void SyncNode::accept(TypeVisitor* v)
{
	v->visit(this);
}

} // namespace analysis