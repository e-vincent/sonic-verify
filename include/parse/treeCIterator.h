#ifndef __TREE_C_ITERATOR_H__
#define __TREE_C_ITERATOR_H__

#include <iterator>
#include <memory>

#include "parse/ast/nodeTree.h"

namespace ast
{

template <class T>
class TreeCIterator : public TreeIterator<T>
{
private:
	ast::NodeTree<std::shared_ptr<T>>& _c_nodeTree;
	T _c_curr;

public:
	TreeCIterator<T>();
	TreeCIterator<T>(ast::NodeTree<std::shared_ptr<T>>& tree);

	TreeCIterator<T> cbegin() const;
	TreeCIterator<T> cend() const;

	TreeCIterator<T> operator++();
};

} // namespace ast

#endif // __TREE_C_ITERATOR_H__