#include "parse/ast/nodes/ifNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

IfNode::IfNode(int index, int parent, int line, int statement, int blkDepth)
: ast::VisitableNode(index, parent, line, statement, blkDepth)
{
		conditionRootIndex = index + 1;
}

void IfNode::setTrueVT(float vt)
{
	trueVT = vt;
}

void IfNode::setFalseVT(float vt)
{
	falseVT = vt;
}

void IfNode::setBlkIndexes(int index, int childCount)
{
	if (childCount == 1)
	{
		trueBlkIndex = index;
	}
	else if (childCount == 2)
	{
		falseBlkIndex = index;
	}
	else
	{
		// error
	}
}

float IfNode::finalVT()
{
	float result;
	if (trueVT > falseVT)
	{
		result = trueVT;
	}
	else
	{
		result = falseVT;
	}
	return result;
}

int IfNode::getConditionRootIndex()
{
	return conditionRootIndex;
}

int IfNode::getTrueIndex()
{
	return trueBlkIndex;
}

int IfNode::getFalseIndex()
{
	return falseBlkIndex;
}

void IfNode::accept(analysis::PTrace* trace, VTimeVisitor* v)
{
	v->visit(trace, this);
}

void IfNode::accept(VTimeVisitor* v, indexes& fill)
{
	v->visit(this, fill);
}

void IfNode::accept(BasicVisitor* v, int index, int childCount)
{
	v->visit(this);
	setBlkIndexes(index, childCount);
}

} // namespace ast