#ifndef __TREE_ITERATOR_H__
#define __TREE_ITERATOR_H__

#include <iterator>
#include <memory>

#include "parse/ast/nodeTree.h"

namespace ast
{

template <class T>
class TreeIterator
{
private:
	ast::NodeTree<std::shared_ptr<T>>& _nodeTree;
	T _curr;

public:
	TreeIterator<T>();
	TreeIterator<T>(ast::NodeTree<std::shared_ptr<T>>& tree);

	TreeIterator<T> begin();
	TreeIterator<T> end();

	TreeIterator<T> operator++();
	bool operator==(const TreeIterator<T>& rhs);
	bool operator!=(const TreeIterator<T>& rhs);
	T& operator*();
};

} // namespace ast

#endif // __TREE_ITERATOR_H__