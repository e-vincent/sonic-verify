#include "parse/treeIterator.h"

namespace ast
{

TreeIterator::TreeIterator(ast::NodeTree& tree, ast::VisitableNode* node) 
	: _nodeTree(tree), _curr(node)
{ }

TreeIterator TreeIterator::operator++()
{
	_curr = _nodeTree.findNext(_curr);
	return *this;
}

TreeIterator TreeIterator::operator++(int)
{
	TreeIterator clone(*this);
	_curr = _nodeTree.findNext(_curr);
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
	return *this->_curr;
}

const ast::VisitableNode& TreeIterator::operator*() const
{
	return *_curr;
}

} // namespace ast