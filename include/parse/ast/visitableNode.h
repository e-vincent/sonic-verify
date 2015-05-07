#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include <list>
#include <iostream>
#include <memory>

#include "rice/Data_Type.hpp"

//#include "parse/ast/intNode.h"

namespace ast
{

class IVisitor;

class VisitableNode
{
private:

protected:
	int statementNum;
	int lineNum;

public:
	std::list<ast::VisitableNode*> children;
//	std::list<std::shared_ptr<ast::VisitableNode>> children;
	std::string value;
	int index;
	int parent;

	//operator IntNode() const;

	void accept(IVisitor v);

	virtual int line();
	virtual int statement();
};

} // namespace ast

#endif // __VISITABLE_NODE_H__