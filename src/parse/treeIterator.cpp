#include "parse/treeIterator.h"
#include "parse/treeCIterator.h"

namespace ast
{

template <class T>
TreeIterator<T>::TreeIterator() 
{
	_nodeTree = NULL;
	_curr 	  = NULL;
}

template <class T>
TreeIterator<T>::TreeIterator(ast::NodeTree<T>& tree) 
		: _nodeTree(tree), _curr(*tree->rootNode) { }

template <class T>
TreeIterator<T> ast::TreeIterator<T>::begin()
{
	return iterator(*_nodeTree->rootNode);
}

template <class T>
TreeIterator<T> TreeIterator<T>::end()
{
	return NULL;
}

template <class T>
TreeIterator<T> TreeIterator<T>::operator++()
{

}

template <class T>
bool TreeIterator<T>::operator==(const TreeIterator<T>& rhs)
{
	return *this == *rhs;
}

template <class T>
bool TreeIterator<T>::operator!=(const TreeIterator<T>& rhs)
{
	return !(this == rhs);
}

template <class T>
T& TreeIterator<T>::operator*()
{
	return _curr;
}


template <class T>
TreeCIterator<T>::TreeCIterator() 
{
	_c_nodeTree	= NULL;
	_c_curr		= NULL;
}

template <class T>
TreeCIterator<T>::TreeCIterator(ast::NodeTree<T>& tree) 
		: _c_nodeTree(tree), _c_curr(*tree->rootNode) { }

template <class T>
TreeCIterator<T> ast::TreeCIterator<T>::cbegin() const
{
	return const_iterator(*_c_nodeTree->rootNode);
}

template <class T>
TreeCIterator<T> TreeCIterator<T>::cend() const
{
	return NULL;
}

} // namespace ast