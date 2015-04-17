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
};

} // namespace ast

#endif // __BASICVISITOR_H__