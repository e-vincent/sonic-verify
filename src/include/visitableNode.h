#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>

#include "rice/Data_Type.hpp"

namespace ast
{

class Visitor;

class VisitableNode
{
private:

protected:
	std::string value;
	int index;
	int parent;

	std::list<ast::VisitableNode*> _children;

public:
	void accept(Visitor v);
};

} // namespace ast

#endif // __VISITABLE_NODE_H__