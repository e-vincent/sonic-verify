#include "parse/ast/vTimeVisitor.h"

namespace ast
{
	
VTimeVisitor::VTimeVisitor() { }

void VTimeVisitor::visit(ast::RootNode* rootNode)
{
	std::cout << "Visiting Root " << rootNode->value << "\n";
}

void VTimeVisitor::visit(ast::BodyNode* bodyNode)
{
	std::cout << "Visiting BodyNode " << bodyNode->value << "\n";		
}

void VTimeVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";		
}

void VTimeVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting IntNode " << floatNode->val() << "\n";		
}

} // namespace ast