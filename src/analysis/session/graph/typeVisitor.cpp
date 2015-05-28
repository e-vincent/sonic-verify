#include "analysis/session/graph/typeVisitor.h"

namespace analysis
{

TypeVisitor::TypeVisitor() { }

void TypeVisitor::visit(graph::CueNode* cueNode)
{
	cueNode->appendSType("!");
}

void TypeVisitor::visit(graph::CueNode* cueNode, std::string& type, std::vector<std::pair<std::string, std::string>> interactions)
{
	bool flag = false;
	std::string compound = "(";
	for (auto action : interactions)
	{
		std::string type;
		type.append(action.first).append(action.second);
		if (flag)
		{
			compound.append("&&");
		}
		flag = true;
		compound.append(type);
	}
	compound.append(")").append(cueNode->toSType());

	type.append(compound);
}

void TypeVisitor::visit(graph::SyncNode* syncNode)
{
	syncNode->appendSType("?");
}

void TypeVisitor::visit(graph::SyncNode* syncNode, std::string& type, std::vector<std::pair<std::string, std::string>> interactions)
{
	bool flag = false;
	std::string compound = "(";
	for (auto action : interactions)
	{
		std::string type;
		type.append(action.first).append(action.second);
		if (flag)
		{
			compound.append("||");
		}
		flag = true;
		compound.append(type);
	}
	compound.append(")").append(syncNode->toSType());

	type.append(compound);
}

} // namespace analysis