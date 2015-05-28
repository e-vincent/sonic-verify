#ifndef __SYM_NODE_H__
#define __SYM_NODE_H__

#include "parse/ast/nodes/visitableNode.h"
#include "analysis/session/graph/typeVisitor.h"

namespace ast
{

class SymNode : public ast::VisitableNode
{
private:
	std::string symbol;

protected:

public:
	SymNode(std::string symbol, int index, int parent, int line, int statement, int blkDepth);

	void accept(analysis::PTrace* trace, ast::VTimeVisitor* v);
	std::string acceptType();

	std::string sym();
};

} // namespace ast

#endif // __SYM_NODE_H__