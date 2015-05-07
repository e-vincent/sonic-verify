#ifndef __TREE_ITERATOR_H__
#define __TREE_ITERATOR_H__

#include <memory>

#include "parse/ast/nodeTree.h"
#include "parse/ast/visitableNode.h"

namespace ast
{

class NodeTree;

class TreeIterator
{
private:
	ast::NodeTree& _nodeTree;
	ast::VisitableNode* _curr;

public:
	TreeIterator(ast::NodeTree& tree, ast::VisitableNode* node);

	TreeIterator operator++();
	TreeIterator operator++(int);
	bool operator==(const TreeIterator& rhs);
	bool operator!=(const TreeIterator& rhs);

	ast::VisitableNode& operator*();
	const ast::VisitableNode& operator*() const;
};

} // namespace ast

#endif // __TREE_ITERATOR_H__