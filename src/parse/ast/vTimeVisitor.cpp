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
	analysis::PTrace::test();
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
	if (this->detectSleep)
	{
		analysis::PTrace::setVT((float) intNode->val());
		this->detectSleep = false;
	}		

	std::cout << "VT at: " << analysis::PTrace::vT() << "\n";
}

void VTimeVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting IntNode " << floatNode->val() << "\n";		
}

} // namespace ast