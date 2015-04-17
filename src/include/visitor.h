#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <iostream>

#include "parse/ast/visitableNode.h"

namespace ast
{

class Visitor
{
public:
	void visit(ast::VisitableNode* visitableNode);
};

} // namespace ast

#endif // __VISITOR_H__