#ifndef __IVISITOR_H__
#define __IVISITOR_H__

#include <iostream>

#include "parse/ast/rootNode.h"
#include "parse/ast/bodyNode.h"
#include "parse/ast/intNode.h"
#include "parse/ast/floatNode.h"

namespace ast
{

class IVisitor
{
public:
	virtual ~IVisitor() {}

	virtual void visit(ast::RootNode* rootNode) = 0;
	virtual void visit(ast::BodyNode* bodyNode) = 0;
	virtual void visit(ast::IntNode* intNode) = 0;
	virtual void visit(ast::FloatNode* floatNode) = 0;
};

} // namespace ast

#endif // __IVISITOR_H__