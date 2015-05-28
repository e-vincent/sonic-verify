#ifndef __SEND_NODE_H__
#define __SEND_NODE_H__

#include "parse/ast/nodes/visitableNode.h"

namespace ast
{

class SendNode : public ast::VisitableNode
{
private:
	std::string sendType;
	std::string funcName; // used only if type == "function"

protected:

public:
	SendNode(int index, int parent, int line, int statement, int blkDepth);

	void accept(analysis::PTrace* trace, ast::VTimeVisitor* v);
	void accept(ast::BasicVisitor* v, std::string sym);
	void setType(std::string s);
	void setFuncName(std::string s);

	std::string type();
	std::string func();
};

} // namespace ast

#endif // __SEND_NODE_H__