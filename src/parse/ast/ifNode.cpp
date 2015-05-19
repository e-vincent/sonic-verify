#include "parse/ast/ifNode.h"
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

void IfNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

} // namespace ast