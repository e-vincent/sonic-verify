#ifndef __VTIME_VISITOR_H__
#define __VTIME_VISITOR_H__

#include "parse/ast/iVisitor.h"

#include "analysis/pTrace.h"

namespace ast
{

class VTimeVisitor : public IVisitor
{
private:
	bool detectSleep;
	bool defineCall;

public:
	VTimeVisitor();

	virtual void visit(ast::RootNode* rootNode);
	virtual void visit(ast::BodyNode* bodyNode);
	virtual void visit(ast::IntNode* intNode);
	virtual void visit(ast::FloatNode* floatNode);
	virtual void visit(ast::SymNode* symNode);
	virtual void visit(ast::SendNode* sendNode);
};

} // namespace ast

#endif // __VTIME_VISITOR_H__