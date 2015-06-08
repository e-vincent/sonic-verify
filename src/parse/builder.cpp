#include "parse/builder.h"

ast::NodeTree* Builder::tree = NULL;
std::map<int, bool> Builder::exits;

Builder::Builder()
{
	Builder::tree = new ast::NodeTree();
	visitor = new ast::BasicVisitor();
	ifChildCount = 0;
}

Builder::~Builder()
{
	delete Builder::tree;
	delete visitor;
}

ast::BodyNode* Builder::makeNode(Rice::Symbol token, int index, 
		int parent, int line, int statement, int blkDepth)
{
	return new ast::BodyNode(token.str(), index, parent, line, statement, blkDepth);
}

ast::IntNode* Builder::makeInt(int num, int index, int parent,
		int line, int statement, int blkDepth)
{
	return new ast::IntNode(num, index, parent, line, statement, blkDepth);
}

ast::FloatNode* Builder::makeFloat(float num, int index, int parent,
		int line, int statement, int blkDepth)
{
	return new ast::FloatNode(num, index, parent, line, statement, blkDepth);
}

ast::SymNode* Builder::makeSymbol(std::string sym, int index, int parent,
		int line, int statement, int blkDepth)
{
	return new ast::SymNode(sym, index, parent, line, statement, blkDepth);
}

ast::SendNode* Builder::makeSend(int index, int parent, int line, int statement, int blkDepth)
{
	return new ast::SendNode(index, parent, line, statement, blkDepth);
}

ast::IfNode* Builder::makeIf(int index, int parent, int line, int statement, int blkDepth)
{
	ifIndexes.push(index);
	return new ast::IfNode(index, parent, line, statement, blkDepth);
}

void Builder::makeRoot(Rice::Symbol root)
{
	ast::RootNode* rootNode = new ast::RootNode(root.str());
	Builder::tree->setRoot(rootNode);	
}

void Builder::addNode(Rice::Symbol nodeType, int index, 
		int parent, int line, int statement, int blkDepth)
{
	if (!ifIndexes.empty())
	{
		checkIfState(index, parent);
	}
	
	ast::VisitableNode* node;
	if (nodeType.str().compare("send") == 0)
	{
		lastSend = index;
		node = makeSend(index, parent, line, statement, blkDepth);
	}
	else
	{
		node = makeNode(nodeType.str(), index, parent, line, statement, blkDepth);
	}

	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addValue(std::string val, int index, int parent, 
		int line, int statement, int blkDepth)
{
	ast::BodyNode* node = makeNode(val, index, parent, line, statement, blkDepth);
	Builder::tree->addNode(node, parent);
	define = (val == "define");
}

void Builder::addNumber(std::string num, int index, 
		int parent, int line, int statement, int blkDepth)
{
	float value = std::stof(num.c_str());
	ast::VisitableNode* node;
	if (remainder(value, 1) == 0)
	{
		node = makeInt((int)value, index, parent, line, statement, blkDepth);
	} 
	else
	{
		node = makeFloat(value, index, parent, line, statement, blkDepth);
	}

	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addSymbol(std::string sym, int index,
		int parent, int line, int statement, int blkDepth)
{
	ast::SymNode* node = makeSymbol(sym, index, parent, line, statement, blkDepth);
	Builder::tree->addNode(node, parent);

	// update last send if function name is being defined
	if (define)
	{
		ast::VisitableNode* send = Builder::tree->findNode(lastSend);
		send->accept(visitor, sym);
		define = false;
	}
}

void Builder::addIf(int index, int parent, int line, int statement, int blkDepth)
{
	ast::IfNode* node = makeIf(index, parent, line, statement, blkDepth);
	Builder::tree->addNode(node, parent);
}

void Builder::setTreeSize(int treeSize, int lineCount)
{
	Builder::tree->setSize(treeSize);
	Builder::tree->setLineCount(lineCount);
}

void Builder::exitFuncs(int statement)
{
	exits[statement] = false;
}

void Builder::checkIfState(int index, int parent)
{
	if (parent == ifIndexes.top())
	{
		++ifChildCount;
		ast::VisitableNode* ifNode = Builder::tree->findNode(parent);
		ifNode->accept(visitor, index, ifChildCount);

		if (ifChildCount == 2)
		{
			ifChildCount = 0;
			ifIndexes.pop();
		}
	}
}

std::map<int, bool> Builder::getExitMap()
{
	return exits;
}
