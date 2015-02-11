#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <iostream>
#include "parse/ast/rootNode.h"

namespace ast
{

class Visitor
{
public:
	void visit(ast::RootNode* rootNode);
};

} // namespace ast

#endif // __VISITOR_H__