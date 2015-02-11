#include "parse/ast/rootNode.h"
#include "parse/ast/visitor.h"

namespace ast
{

RootNode::RootNode()
{

}

void RootNode::accept(Visitor v)
{
	v.visit(this);
}

} // namespace ast