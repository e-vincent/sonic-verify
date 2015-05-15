#include "analysis/session/cueNode.h"
#include "analysis/session/typeVisitor.h"

namespace analysis
{

CueNode::CueNode(int index, int line, std::string symbol, int blk)
: GraphNode(index, line, symbol, blk) { }

void CueNode::accept(TypeVisitor* v)
{
	v->visit(this);
}

} // namespace analysis