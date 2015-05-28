#include "analysis/session/graph/nodes/cueNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace graph
{

CueNode::CueNode(int index, int line, std::string symbol)
: GraphNode(index, line, symbol) { }

void CueNode::accept(analysis::TypeVisitor* v)
{
	v->visit(this);
}

void CueNode::accept(analysis::TypeVisitor* v, std::string& type, std::vector<std::pair<std::string, std::string>> interactions)
{
	v->visit(this, type, interactions);
}

} // namespace graph