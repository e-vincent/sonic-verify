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

	// carry forward the cumulative VT in the event 
	// we pass through begin/block nodes
	analysis::PTrace::createTrace(bodyNode->statement());
}

void VTimeVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";
	float conVT;

	if (this->detectSleep)
	{
		conVT = (float) intNode->val();
		this->detectSleep = false;
		std::cout << "reset bool" << "\n";
	}		
	else
	{
		conVT = 0.0;
	}

	analysis::PTrace::createTrace(conVT, intNode->statement());
}

void VTimeVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting FloatNode " << floatNode->val() << "\n";
	float conVT;

	if (this->detectSleep)
	{
		conVT = floatNode->val();
		this->detectSleep = false;
		std::cout << "reset bool" << "\n";
	}		
	else
	{
		conVT = 0.0;
	}

	std::cout << "contributing " << conVT << "\n";
	analysis::PTrace::createTrace(conVT, floatNode->statement());
}

void VTimeVisitor::visit(ast::SymNode* symNode)
{
	std::cout << "Visiting SymNode " << symNode->value << "\n";
}

void VTimeVisitor::visit(ast::SendNode* sendNode)
{
	std::cout << "Visiting SendNode " << sendNode->value << "\n";
}

} // namespace ast