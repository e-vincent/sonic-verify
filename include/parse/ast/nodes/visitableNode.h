#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>
#include <memory>

#include "rice/Data_Type.hpp"
#include "parse/ast/structs.h"

namespace analysis
{ class PTrace; }

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
	int blkIndex;
	int index;
	int parent;

	VisitableNode();
	VisitableNode(int index, int parent, int line, int statement, int blkDepth, int blkIndex);

	virtual void accept(analysis::PTrace*, ast::VTimeVisitor*) = 0;
	virtual void accept(ast::VTimeVisitor*, indexes&) {};
	virtual void accept(ast::BasicVisitor*, std::string) {};
	virtual void accept(ast::BasicVisitor*, int, int) {};

	virtual std::string acceptType();

	virtual int line();
	virtual int statement();
	virtual int blockDepth();
};

} // namespace ast

#endif // __VISITABLE_NODE_H__