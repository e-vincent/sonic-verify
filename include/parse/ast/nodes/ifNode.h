#ifndef __IF_NODE_H__
#define __IF_NODE_H__

#include "parse/ast/nodes/visitableNode.h"

namespace ast
{

class IfNode : public ast::VisitableNode
{
private:
	int conditionRootIndex;
	int trueBlkIndex;
	int falseBlkIndex;
	float trueVT;
	float falseVT;

public:
	IfNode(int index, int parent, int line, int statement, int blkDepth, int blkIndex);

	void setTrueVT(float vt);
	void setFalseVT(float vt);
	void setBlkIndexes(int index, int childCount);

	float finalVT();
	int getConditionRootIndex();
	int getTrueIndex();
	int getFalseIndex();

	virtual void accept(analysis::PTrace* trace, VTimeVisitor* v);
	virtual void accept(VTimeVisitor* v, indexes& fill);
	virtual void accept(BasicVisitor* v, int index, int childCount);
};

} // namespace ast

#endif // __IF_NODE_H__