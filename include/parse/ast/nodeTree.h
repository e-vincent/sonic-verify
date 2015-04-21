#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <iostream>

#include "parse/ast/visitableNode.h"

namespace ast
{

class NodeTree
{
public:
	ast::VisitableNode* rootNode;

	NodeTree();

	ast::VisitableNode* root();
	ast::VisitableNode* findNode(int index);
	
	void setRoot(ast::VisitableNode* rootNode);
	void addNode(ast::VisitableNode* node, int parent);

};

} // ast

#endif // __NODE_TREE_H__