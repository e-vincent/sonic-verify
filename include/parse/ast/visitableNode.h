#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

#include "parse/ast/visitor.h"

namespace ast
{

class VisitableNode
{
	virtual void accept(Visitor v);
};

} // ast

#endif // __VISITABLE_NODE_H__