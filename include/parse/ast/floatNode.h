#ifndef __FLOAT_NODE_H__
#define __FLOAT_NODE_H__

#include "parse/ast/visitableNode.h"

namespace ast
{

class FloatNode : public ast::VisitableNode
{
private:
	float num;

protected:

public:
	FloatNode();
	FloatNode(float num, int index, int parent, int line, int statement);

	float val();
	void accept(ast::VTimeVisitor* v);
};

} // namespace ast

#endif // __FLOAT_NODE_H__