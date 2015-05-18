#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>
#include <memory>

#include "rice/Data_Type.hpp"

#include "analysis/session/graph/typeVisitor.h"

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
	int blkDepth;

public:
	std::list<ast::VisitableNode*> children;
	std::string value;
	int index;
	int parent;

	VisitableNode();
	VisitableNode(int index, int parent, int line, int statement, int blkDepth);

	virtual void accept(ast::VTimeVisitor*) = 0;
	virtual void accept(ast::BasicVisitor*, std::string);
	virtual std::string acceptType();

	virtual int line();
	virtual int statement();
	virtual int blockDepth();
};

} // namespace ast

#endif // __VISITABLE_NODE_H__