#ifndef __BASICVISITOR_H__
#define __BASICVISITOR_H__

#include "parse/ast/iVisitor.h"

namespace ast
{

class BasicVisitor : public IVisitor
{
public:
	BasicVisitor();

	virtual void visit(ast::RootNode* rootNode);
	virtual void visit(ast::BodyNode* bodyNode);
	virtual void visit(ast::IntNode* intNode);
	virtual void visit(ast::FloatNode* floatNode);
	virtual void visit(ast::SymNode* symNode);
	virtual void visit(ast::SendNode* sendNode);
	virtual void visit(ast::IfNode* ifNode);
};

} // namespace ast

#endif // __BASICVISITOR_H__