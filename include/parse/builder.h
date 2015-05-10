#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <iostream>
#include <memory>
#include <math.h>

#include "main.h"

#include "parse/ast/basicVisitor.h"

#include "parse/ast/nodeTree.h"
#include "parse/ast/visitableNode.h"
#include "parse/ast/rootNode.h"
#include "parse/ast/bodyNode.h"
#include "parse/ast/intNode.h"
#include "parse/ast/floatNode.h"
#include "parse/ast/symNode.h"
#include "parse/ast/sendNode.h"

class Builder
{
private:
	int lastSend;
	bool define;

public:
	static ast::NodeTree* tree;
	ast::BasicVisitor* visitor;

	Builder();
	~Builder();

	ast::BodyNode* makeNode(Rice::Symbol token, int index, int parent, int line, int statement);
	ast::IntNode* makeInt(int num, int index, int parent, int line, int statement);
	ast::FloatNode* makeFloat(float num, int index, int parent, int line, int statement);
	ast::SymNode* makeSymbol(std::string sym, int index, int parent, int line, int statement);
	ast::SendNode* makeSend(int index, int parent, int line, int statement);

	void makeRoot(Rice::Symbol root);
	void addNode(Rice::Symbol nodeType, int index, int parent, int line, int statement);
	void addValue(std::string val, int index, int parent, int line, int statement);
	void addNumber(std::string num, int index, int parent, int line, int statement);
	void addSymbol(std::string sym, int index, int parent, int line, int statement);

	void setTreeSize(int treeSize, int lineCount);
};

#endif // __BUILDER_H__