#ifndef __VISITABLE_NODE_H__
#define __VISITABLE_NODE_H__

namespace ast
{

class Visitor;

class VisitableNode
{
public:
	void accept(Visitor v);
};

} // ast

#endif // __VISITABLE_NODE_H__