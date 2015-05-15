#ifndef __BASIC_VISITOR_H__
#define __BASIC_VISITOR_H__

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
};

} // namespace ast

#endif // __BASIC_VISITOR_H__