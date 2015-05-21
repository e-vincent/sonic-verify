#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

void TypeVisitor::visit(graph::CueNode* cueNode)
{
	std::cout << "Visiting Cue " << cueNode->symbol << "\n";
	cueNode->setSType("!");
}

void TypeVisitor::visit(graph::SyncNode* syncNode)
{
	std::cout << "Visiting Sync " << syncNode->symbol << "\n";
	syncNode->setSType("?");
}

} // namespace analysis