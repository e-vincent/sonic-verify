#include "parse/ast/nodeTree.h"

namespace ast
{

template <class T>
NodeTree<T>::NodeTree() {}

template <class T>
T NodeTree<T>::root()
{
	return NodeTree::rootNode;
}

template <class T>
T NodeTree<T>::findNode(int index)
{
	T curr = this->rootNode;
	T result = NULL;

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

		T old = curr;		
		for (T child : curr->children)
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

template <class T>
void NodeTree<T>::setRoot(T rootNode)
{
	this->rootNode = rootNode;
}

template <class T>
void NodeTree<T>::addNode(T node, int parent)
{
	T parNode = findNode(parent);
	parNode->children.push_back(node);
}

} // namespace ast