#ifndef __VTIME_VISITOR_H__
#define __VTIME_VISITOR_H__

#include "parse/ast/iVisitor.h"

#include "analysis/pTrace.h"
#include "parse/ast/structs.h"

namespace analysis
{ class PTrace; }

namespace ast
{

class VTimeVisitor : public IVisitor
{
private:
	bool detectSleep;
	bool defineCall;

public:
	VTimeVisitor();

	// stubs
	virtual void visit(ast::RootNode*) {};
	virtual void visit(ast::BodyNode*) {};
	virtual void visit(ast::IntNode*) {};
	virtual void visit(ast::FloatNode*) {};
	virtual void visit(ast::SymNode*) {};
	virtual void visit(ast::SendNode*) {};
	virtual void visit(ast::IfNode*) {};
	virtual void visit(analysis::PTrace*, ast::RootNode*) {};
	
	virtual void visit(analysis::PTrace* trace, ast::BodyNode* bodyNode);
	virtual void visit(analysis::PTrace* trace, ast::IntNode* intNode);
	virtual void visit(analysis::PTrace* trace, ast::FloatNode* floatNode);
	virtual void visit(analysis::PTrace* trace, ast::SymNode* symNode);
	virtual void visit(analysis::PTrace* trace, ast::SendNode* sendNode);
	virtual void visit(analysis::PTrace* trace, ast::IfNode* ifNode);
	virtual void visit(ast::IfNode* ifNode, indexes& fill);
};

} // namespace ast

#endif // __VTIME_VISITOR_H__