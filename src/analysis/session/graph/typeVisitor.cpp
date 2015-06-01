#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

TypeVisitor::TypeVisitor() { }

void TypeVisitor::visit(graph::CueNode* cueNode)
{
	cueNode->setSType("!");
}

void TypeVisitor::visit(graph::CueNode* cueNode, std::string& type, 
		std::vector<std::pair<std::string, std::string>> interactions)
{
	typer(cueNode, type, "&&", interactions);
}

void TypeVisitor::visit(graph::SyncNode* syncNode)
{
	syncNode->setSType("?");
}

void TypeVisitor::visit(graph::SyncNode* syncNode, std::string& type, 
		std::vector<std::pair<std::string, std::string>> interactions)
{
	typer(syncNode, type, "||", interactions);
}

void TypeVisitor::typer(graph::GraphNode* node, std::string& type, std::string typeSymbol,
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

	// ensure we have more characters than the empty string
	// will mean we've built some types before now
	if (type > "")
	{
		type.append(".");
	}

	type.append(compound);	
}

} // namespace analysis