#include "parse/treeIterator.h"

namespace ast
{

TreeIterator::TreeIterator(ast::NodeTree& tree, ast::VisitableNode* node) 
	: _nodeTree(tree), _curr(node)
{
//	_curr = ;
	//std::cout << _nodeTree.root()->value << "\n";
}

TreeIterator TreeIterator::operator++()
{
	int next = _curr->index + 1;
	_curr = _nodeTree.findNode(next);
	return *this;
}

TreeIterator TreeIterator::operator++(int)
{
	TreeIterator clone(*this);
	int next = _curr->index + 1;
	_curr = _nodeTree.findNode(next);
	return clone;	
}

bool TreeIterator::operator==(const TreeIterator& rhs)
{
	return this->_curr == rhs._curr;
}

bool TreeIterator::operator!=(const TreeIterator& rhs)
{
	return !(*this == rhs);
}

ast::VisitableNode& TreeIterator::operator*()
{
	return *_curr;
}

const ast::VisitableNode& TreeIterator::operator*() const
{
	return *_curr;
}

} // namespace ast