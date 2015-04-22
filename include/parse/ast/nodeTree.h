#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <iostream>

//#include "parse/ast/visitableNode.h"

namespace ast
{

// forward declaration
template <class T> class TreeIterator;
template <class T> class TreeCIterator;

template <class T>
class NodeTree
{
public:
	friend class TreeIterator<T>;
	typedef TreeIterator<T> iterator;
	typedef TreeCIterator<T> const_iterator;
	//typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	std::shared_ptr<T> rootNode;

	NodeTree<T>();

	T root();
	T findNode(int index);
	
	void setRoot(T rootNode);
	void addNode(T node, int parent);

};

} // ast

#endif // __NODE_TREE_H__