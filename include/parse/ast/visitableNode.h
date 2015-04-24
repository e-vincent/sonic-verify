#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>
#include <memory>

#include "rice/Data_Type.hpp"

namespace ast
{

class IVisitor;

class VisitableNode
{
private:

protected:

public:
	std::list<ast::VisitableNode*> children;
//	std::list<std::shared_ptr<ast::VisitableNode>> children;
	std::string value;
	int index;
	int parent;

	void accept(IVisitor v);
};

} // namespace ast

#endif // __VISITABLE_NODE_H__