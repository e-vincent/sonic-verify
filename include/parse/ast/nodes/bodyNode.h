#ifndef __BODY_NODE_H__
#define __BODY_NODE_H__

#include "parse/ast/nodes/visitableNode.h"

namespace ast
{

class BodyNode : public ast::VisitableNode
{
private:

protected:

public:
	BodyNode(std::string node, int index, int parent, int line, int statement, int blkDepth, int blkIndex);

	void accept(analysis::PTrace* trace, ast::VTimeVisitor* v);
	bool isFuncCall();
};

} // namespace ast

#endif // __BODY_NODE_H__