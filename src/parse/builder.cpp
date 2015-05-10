#include "parse/builder.h"

ast::NodeTree* Builder::tree = NULL;

Builder::Builder()
{
	Builder::tree = new ast::NodeTree();
	visitor = new ast::BasicVisitor();
}

Builder::~Builder()
{
	delete Builder::tree;
}

ast::BodyNode* Builder::makeNode(Rice::Symbol token, int index, 
		int parent, int line, int statement)
{
	return new ast::BodyNode(token.str(), index, parent, line, statement);
}

ast::IntNode* Builder::makeInt(int num, int index, int parent,
		int line, int statement)
{
	return new ast::IntNode(num, index, parent, line, statement);
}

ast::FloatNode* Builder::makeFloat(float num, int index, int parent,
		int line, int statement)
{
	return new ast::FloatNode(num, index, parent, line, statement);
}

ast::SymNode* Builder::makeSymbol(std::string sym, int index, int parent,
		int line, int statement)
{
	return new ast::SymNode(sym, index, parent, line, statement);
}

ast::SendNode* Builder::makeSend(int index, int parent, int line, int statement)
{
	return new ast::SendNode(index, parent, line, statement);
}

void Builder::makeRoot(Rice::Symbol root)
{
	ast::RootNode* rootNode = new ast::RootNode(root.str());
	Builder::tree->setRoot(rootNode);
	define = false;
}

void Builder::addNode(Rice::Symbol nodeType, int index, 
		int parent, int line, int statement)
{
	ast::VisitableNode* node;
	if (nodeType.str().compare("send"))
	{
		lastSend = index;
		node = makeSend(index, parent, line, statement);
	}
	else
	{
		node = makeNode(nodeType.str(), index, parent, line, statement);
	}
	Builder::tree->addNode(node, parent);

	define = nodeType.str().compare("define");
}

void Builder::addValue(std::string val, int index, int parent, 
		int line, int statement)
{
	ast::BodyNode* node = makeNode(val, index, parent, line, statement);
	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addNumber(std::string num, int index, 
		int parent, int line, int statement)
{
	float value = std::stof(num.c_str());
	ast::VisitableNode* node;
	if (remainder(value, 1) == 0)
	{
		node = makeInt((int)value, index, parent, line, statement);
	} 
	else
	{
		node = makeFloat(value, index, parent, line, statement);
	}

	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addSymbol(std::string sym, int index,
		int parent, int line, int statement)
{
	ast::SymNode* node = makeSymbol(sym, index, parent, line, statement);
	Builder::tree->addNode(node, parent);

	// update last send if function name is being defined
	if (define)
	{
		ast::VisitableNode* send = Builder::tree->findNode(lastSend);
		send->accept(visitor, sym);
	}

	define = false;
}

void Builder::setTreeSize(int treeSize, int lineCount)
{
	Builder::tree->setSize(treeSize);
	Builder::tree->setLineCount(lineCount);
}