#ifndef __IF_NODE_H__
#define __IF_NODE_H__

#include "parse/ast/visitableNode.h"

namespace ast
{

class IfNode : public ast::VisitableNode
{
private:
	int conditionRootIndex;
	float trueVT;
	float falseVT;

public:
	IfNode(int index, int parent, int line, int statement, int blkDepth);

	void setTrueVT(float vt);
	void setFalseVT(float vt);
	float finalVT();
	int getConditionRootIndex();

	virtual void accept(VTimeVisitor* v);
};

} // namespace ast

#endif // __IF_NODE_H__