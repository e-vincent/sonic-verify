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
	ast::VisitableNode* curr = this->rootNode;
	ast::VisitableNode* result = NULL;

	while (curr != NULL)
	{
		if (curr->index == index)
		{
			result = curr;
		}

		// this is written terribly
		if (!curr->children.size())
		{
			break;
		}

		ast::VisitableNode* old = curr;		
		for (ast::VisitableNode* child : curr->children)
		{
			if (child->index <= index)
			{
				curr = child;
			}
		}

		// if curr didn't change there were no children to search further
		if (curr == old)
		{
			curr = NULL;
		}
	}

	return result;
}

void NodeTree::setRoot(ast::VisitableNode* rootNode)
{
	this->rootNode = rootNode;
}

void NodeTree::addNode(ast::VisitableNode* node, int parent)
{
	ast::VisitableNode* parNode = findNode(parent);
	parNode->children.push_back(node);
}

} // namespace ast