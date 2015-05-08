#include "parse/ast/vTimeVisitor.h"

namespace ast
{
	
VTimeVisitor::VTimeVisitor()
{
	this->detectSleep = false;
}

void VTimeVisitor::visit(ast::RootNode* rootNode)
{
	std::cout << "Visiting Root " << rootNode->value << "\n";
}

void VTimeVisitor::visit(ast::BodyNode* bodyNode)
{
	std::cout << "Visiting BodyNode " << bodyNode->value << "\n";
	if ("sleep" == bodyNode->value)
	{
		std::cout << "flip bool" << "\n";
		this->detectSleep = true;
	}		
}

void VTimeVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";
	std::cout << "CURR STATEMENT: " << intNode->statement() << "\n";
	float conVT;

	if (this->detectSleep)
	{
		conVT = (float) intNode->val();
		this->detectSleep = false;
	}		
	else
	{
		conVT = 0.0;
	}

	analysis::PTrace::setVT(conVT, intNode->statement());
	std::cout << "VT at: " << analysis::PTrace::cumVTAt(intNode->statement()) << "\n";
}

void VTimeVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting IntNode " << floatNode->val() << "\n";		
}

} // namespace ast