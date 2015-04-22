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

} // namespace ast