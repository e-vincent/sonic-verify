#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <iostream>
#include <iterator>
#include <memory>

#include "parse/treeIterator.h"
#include "parse/ast/visitableNode.h"

namespace ast
{

// forward declaration
class TreeIterator;
class TreeCIterator;

class NodeTree
{
public:
	typedef TreeIterator iterator;
	typedef TreeCIterator const_iterator;

	// typedef size_t size_type;
	// typedef T value_type;
	// typedef T* pointer;
	// typedef T& reference;

	ast::VisitableNode* rootNode;

	NodeTree();

	TreeIterator* begin();
	TreeIterator* end();

	ast::VisitableNode* root();
	ast::VisitableNode* findNode(int index);

	void setRoot(ast::VisitableNode* rootNode);
	void addNode(ast::VisitableNode* node, int parent);
};

// inline std::ostream& operator<<(std::ostream& stream, const NodeTree&)
// {
// 	stream << "Not implemented\n";
// 	return stream;
// }


} // ast

#endif // __NODE_TREE_H__