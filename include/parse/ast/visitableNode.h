#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>
#include <memory>

#include "rice/Data_Type.hpp"

namespace ast
{

class BasicVisitor;
class VTimeVisitor;
class VisitableNode
{
private:

protected:
	int statementNum;
	int lineNum;

public:
	std::list<ast::VisitableNode*> children;
	std::string value;
	int index;
	int parent;

	virtual void accept(ast::VTimeVisitor*) = 0;
	virtual void accept(ast::BasicVisitor*, std::string);

	virtual int line();
	virtual int statement();
};

} // namespace ast

#endif // __VISITABLE_NODE_H__