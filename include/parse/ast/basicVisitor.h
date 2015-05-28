#ifndef __BASIC_VISITOR_H__
#define __BASIC_VISITOR_H__

#include "parse/ast/iVisitor.h"

namespace ast
{

class BasicVisitor : public IVisitor
{
public:
	BasicVisitor() {};

	virtual void visit(ast::RootNode*) {};
	virtual void visit(ast::BodyNode*) {};
	virtual void visit(ast::IntNode*) {};
	virtual void visit(ast::FloatNode*) {};
	virtual void visit(ast::SymNode*) {};
	virtual void visit(ast::SendNode*) {};
	virtual void visit(ast::IfNode*) {};
};

} // namespace ast

#endif // __BASIC_VISITOR_H__
