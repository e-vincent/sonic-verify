#ifndef __TREE_C_ITERATOR_H__
#define __TREE_C_ITERATOR_H__

#include <iterator>
#include <memory>

#include "parse/ast/nodeTree.h"

namespace ast
{

class TreeCIterator : public TreeIterator
{
private:
	ast::NodeTree& _c_nodeTree;
	ast::VisitableNode _c_curr;

public:
	TreeCIterator()
	{
		_c_nodeTree	= NULL;
		_c_curr		= NULL;
	}
	
	TreeCIterator(ast::NodeTree& tree) 
		: _c_nodeTree(tree), _c_curr(*tree.root()) { }

	// TreeCIterator cbegin() const
	// {
	// 	return (*_c_nodeTree->rootNode);
	// }
	
	TreeCIterator cend() const
	{
		return NULL;
	}

	TreeCIterator operator++() {}
};

} // namespace ast

#endif // __TREE_C_ITERATOR_H__