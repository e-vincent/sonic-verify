#ifndef __BODY_NODE_H__
#define __BODY_NODE_H__

#include "parse/ast/visitableNode.h"

namespace ast
{

class BodyNode : public ast::VisitableNode
{
private:

protected:

public:
	BodyNode();
	BodyNode(std::string node, int index, int parent, int line, int statement);

	void accept(ast::VTimeVisitor* v);
};

} // namespace ast

#endif // __BODY_NODE_H__