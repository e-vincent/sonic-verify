#include "analysis/session/graph/nodes/cueNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

CueNode::CueNode(int index, int line, std::string symbol)
: GraphNode(index, line, symbol) { }

void CueNode::accept(TypeVisitor* v)
{
	v->visit(this);
}

} // namespace analysis