#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

TypeVisitor::TypeVisitor() { }

void TypeVisitor::visit(graph::CueNode* cueNode)
{
	cueNode->setSType("!");
}

void TypeVisitor::visit(graph::CueNode* cueNode, 
		std::vector<std::pair<std::string, std::string>> interactions)
{
	typer(cueNode, "&&", interactions);
}

void TypeVisitor::visit(graph::SyncNode* syncNode)
{
	syncNode->setSType("?");
}

void TypeVisitor::visit(graph::SyncNode* syncNode, 
		std::vector<std::pair<std::string, std::string>> interactions)
{
	typer(syncNode, "||", interactions);
}

void TypeVisitor::typer(graph::GraphNode* node, std::string typeSymbol,
		std::vector<std::pair<std::string, std::string>> interactions)
{
	bool flag = false;
	std::string compound = node->symbol;
	compound.append(":");
	compound.append("(");
	for (auto action : interactions)
	{
		std::string type;
		type.append(action.first).append(action.second);
		if (flag)
		{
			compound.append(typeSymbol);
		}
		flag = true;
		compound.append(type);
	}
	compound.append(")").append(node->toSType());

	node->setSType(compound);	
}

} // namespace analysis