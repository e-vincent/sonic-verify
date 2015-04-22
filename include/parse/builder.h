#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <iostream>
#include <memory>

#include "main.h"

#include "parse/ast/nodeTree.h"
#include "parse/ast/visitableNode.h"
#include "parse/ast/rootNode.h"
#include "parse/ast/bodyNode.h"

class Builder
{
public:
	static ast::NodeTree<std::shared_ptr<ast::VisitableNode>>* tree;

	Builder();
	~Builder();

	std::shared_ptr<ast::BodyNode> makeNode(Rice::Symbol token, int index, int parent);
	void makeRoot(Rice::Symbol root);
	void addNode(Rice::Symbol nodeType, int index, int parent);
	void addValue(std::string val, int index, int parent);
};

#endif // __BUILDER_H__