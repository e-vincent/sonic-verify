#include "parse/ast/nodeTree.h"

namespace ast
{

NodeTree::NodeTree() {}

ast::VisitableNode* NodeTree::root()
{
	return NodeTree::rootNode;
}

ast::VisitableNode* NodeTree::findNode(int index)
{
	std::cout << "Find Node: " << index << "\n";
	return NULL;
}

void NodeTree::setRoot(ast::VisitableNode* rootNode)
{
	this->rootNode = rootNode;
}

void NodeTree::addNode(ast::VisitableNode* node, 
		int index, int parent)
{
	std::cout << node->value << "\n";
	std::cout << "Add Node: " << index;
	std::cout << " with parents " << parent << "\n";
}

} // namespace ast