#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <iostream>
#include <memory>
#include <math.h>
#include <map>
#include <stack>

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
#include "parse/ast/ifNode.h"

class Builder
{
private:
	std::stack<int> ifIndexes;
	int ifChildCount;
	int lastSend;
	bool define;
	static std::map<int, bool> exits;

public:
	static ast::NodeTree* tree;
	ast::BasicVisitor* visitor;

	Builder();
	~Builder();

	ast::BodyNode* makeNode(Rice::Symbol token, int index, int parent, int line, int statement, int blkDepth);
	ast::IntNode* makeInt(int num, int index, int parent, int line, int statement, int blkDepth);
	ast::FloatNode* makeFloat(float num, int index, int parent, int line, int statement, int blkDepth);
	ast::SymNode* makeSymbol(std::string sym, int index, int parent, int line, int statement, int blkDepth);
	ast::SendNode* makeSend(int index, int parent, int line, int statement, int blkDepth);
	ast::IfNode* makeIf(int index, int parent, int line, int statement, int blkDepth);

	void makeRoot(Rice::Symbol root);
	void addNode(Rice::Symbol nodeType, int index, int parent, int line, int statement, int blkDepth);
	void addValue(std::string val, int index, int parent, int line, int statement, int blkDepth);
	void addNumber(std::string num, int index, int parent, int line, int statement, int blkDepth);
	void addSymbol(std::string sym, int index, int parent, int line, int statement, int blkDepth);
	void addIf(int index, int parent, int line, int statement, int blkDepth);

	void setTreeSize(int treeSize, int lineCount);
	void exitFuncs(int statement);
	void checkIfState(int index, int parent);
	
	static std::map<int, bool> getExitMap();
};

#endif // __BUILDER_H__