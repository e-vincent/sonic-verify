#include "parse/ast/basicVisitor.h"

namespace ast
{
	
BasicVisitor::BasicVisitor() {}

void BasicVisitor::visit(ast::RootNode* rootNode)
{
	std::cout << "Visiting Root " << rootNode->value << "\n";
}

void BasicVisitor::visit(ast::BodyNode* bodyNode)
{
	std::cout << "Visiting BodyNode " << bodyNode->value << "\n";		
}

void BasicVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";		
}

void BasicVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting IntNode " << floatNode->val() << "\n";		
}

void BasicVisitor::visit(ast::SymNode* symNode)
{
	std::cout << "Visiting SymNode " << symNode->value << "\n";
}

void BasicVisitor::visit(ast::SendNode* sendNode)
{
	std::cout << "Visiting SendNode " << sendNode->value << " " << sendNode->index << "\n";
}

void BasicVisitor::visit(ast::IfNode* ifNode)
{
	std::cout << "Visiting IfNode " << ifNode->index << "\n";
}

} // namespace ast