#ifndef __AST_IVISITOR_H__
#define __AST_IVISITOR_H__

#include <iostream>

#include "parse/ast/nodes/nodes.h"

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
	virtual void visit(ast::SymNode* symNode) = 0;
	virtual void visit(ast::SendNode* sendNode) = 0;
};

} // namespace ast

#endif // __AST_IVISITOR_H__