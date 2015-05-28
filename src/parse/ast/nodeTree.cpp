#include "parse/ast/nodeTree.h"

namespace ast
{

NodeTree::NodeTree() { }
NodeTree::NodeTree(ast::VisitableNode* root, int parentSize)
{
	rootNode = root;

	// correct tree sizes
	this->setSize(parentSize); // statement indexing?

	treeTrace = new analysis::PTrace(this);
}

NodeTree::~NodeTree()
{
	delete treeTrace;
}

void NodeTree::setUpTrace()
{
	treeTrace = new analysis::PTrace();
}

ast::TreeIterator NodeTree::begin()
{
	return *(new TreeIterator(*this, rootNode));
}

ast::TreeIterator NodeTree::end()
{
	return *(new TreeIterator(*this, NULL));
}

ast::VisitableNode* NodeTree::root()
{
	return rootNode;
}

ast::VisitableNode* NodeTree::findNode(int index)
{
	ast::VisitableNode* curr   = this->rootNode;
	ast::VisitableNode* result = NULL;

	while (curr != NULL)
	{
		if (curr->index == index)
		{
			result = curr;
		}

		// this is written terribly
		if (curr->children.empty() || result != NULL)
		{
			break;
		}

		ast::VisitableNode* old = curr;		
		for (ast::VisitableNode* child : curr->children)
		{
			if (child->index <= index)
			//if (child->index <= index && child->index > curr->index)
			{
				curr = child;
			}
		}

		// if curr didn't change there were no children to search further
		// we haven't found node so returning null
		if (curr == old)
		{
			curr = NULL;
		}

	}

	return result;
}

ast::VisitableNode* NodeTree::findNext(ast::VisitableNode* node)
{
	int index = node->index + 1;
	ast::VisitableNode* curr = this->rootNode;
	ast::VisitableNode* result = NULL;

	while (curr != NULL)
	{
		if (curr->index == index)
		{
			result = curr;
		}

		// this is written terribly
		if (curr->children.empty())
		{
			break;
		}

		ast::VisitableNode* old = curr;		
		for (ast::VisitableNode* child : curr->children)
		{
			//if (child->index <= index)
			if (child->index <= index && child->index > curr->index)
			{
				curr = child;
			}
		}

		// if curr didn't change there were no children to search further
		// we haven't found node so returning null
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
	std::cout << rootNode->value << "\n";
}

void NodeTree::addNode(ast::VisitableNode* node, int parent)
{
	std::cout << node->value 
			<< " " << node->index << " parent " << parent << "\n";
	ast::VisitableNode* parNode = findNode(parent);
	parNode->children.push_back(node);
}

analysis::PTrace* NodeTree::trace()
{
	return treeTrace;
}

void NodeTree::setSize(int size)
{
	this->treeSize = size;
}

int NodeTree::size()
{
	return this->treeSize;
}

void NodeTree::setLineCount(int count)
{
	this->lines = count;
}

int NodeTree::lineCount()
{
	return this->lines;
}

} // namespace ast