#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

TypeVisitor::TypeVisitor() { }

void TypeVisitor::visit(graph::CueNode* cueNode)
{
	std::cout << "Visiting Cue " << cueNode->symbol << "\n";
	cueNode->appendSType("!");
}

void TypeVisitor::visit(graph::SyncNode* syncNode)
{
	std::cout << "Visiting Sync " << syncNode->symbol << "\n";
	syncNode->appendSType("?");
}

} // namespace analysis