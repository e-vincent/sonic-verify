#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

void TypeVisitor::visit(analysis::CueNode* cueNode)
{
	std::cout << "Visiting Cue " << cueNode->symbol << "\n";
	std::string type = cueNode->symbol;
	type.append("!");
}

void TypeVisitor::visit(analysis::SyncNode* syncNode)
{
	std::cout << "Visiting Sync " << syncNode->symbol << "\n";
}

} // namespace analysis