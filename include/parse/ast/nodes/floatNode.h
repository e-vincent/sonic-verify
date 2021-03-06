#ifndef __FLOAT_NODE_H__
#define __FLOAT_NODE_H__

#include "parse/ast/nodes/visitableNode.h"

namespace ast
{

class FloatNode : public ast::VisitableNode
{
private:
	float num;

protected:

public:
	FloatNode(float num, int index, int parent, int line, int statement, int blkDepth, int blkIndex);

	float val();
	void accept(analysis::PTrace* trace, ast::VTimeVisitor* v);
};

} // namespace ast

#endif // __FLOAT_NODE_H__