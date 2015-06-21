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

int Builder::returnTest()
{
	return Builder::tree->trace()->totalVT();
}

std::string Builder::returnTestTwo()
{
	return "test";//Builder::tree->trace()->sessionTypes[0];
}

Rice::Array Builder::returnCumVTs()
{
	Rice::Array results;
	analysis::PTrace *trace = Builder::tree->trace();

	for (analysis::TData *data : trace->stats)
	{
		Rice::Array elem;
		elem.push(data->cumVT);
		elem.push(data->line);
		results.push(elem);
	}

	return results;
}

ast::BodyNode* Builder::makeNode(Rice::Symbol token, int index, 
		int parent, int line, int statement, int blkDepth, int blkIndex)
{
	return new ast::BodyNode(token.str(), index, parent, line, statement, blkDepth, blkIndex);
}

ast::IntNode* Builder::makeInt(int num, int index, int parent,
		int line, int statement, int blkDepth, int blkIndex)
{
	return new ast::IntNode(num, index, parent, line, statement, blkDepth, blkIndex);
}

ast::FloatNode* Builder::makeFloat(float num, int index, int parent,
		int line, int statement, int blkDepth, int blkIndex)
{
	return new ast::FloatNode(num, index, parent, line, statement, blkDepth, blkIndex);
}

ast::SymNode* Builder::makeSymbol(std::string sym, int index, int parent,
		int line, int statement, int blkDepth, int blkIndex)
{
	return new ast::SymNode(sym, index, parent, line, statement, blkDepth, blkIndex);
}

ast::SendNode* Builder::makeSend(int index, int parent, int line, int statement, int blkDepth, int blkIndex)
{
	return new ast::SendNode(index, parent, line, statement, blkDepth, blkIndex);
}

ast::IfNode* Builder::makeIf(int index, int parent, int line, int statement, int blkDepth, int blkIndex)
{
	ifIndexes.push(index);
	return new ast::IfNode(index, parent, line, statement, blkDepth, blkIndex);
}

void Builder::makeRoot(Rice::Symbol root)
{
	ast::RootNode* rootNode = new ast::RootNode(root.str());
	Builder::tree->setRoot(rootNode);	
}

void Builder::addNode(Rice::Symbol nodeType, int index, 
		int parent, int line, int statement, int blkDepth, int blkIndex)
{
	if (!ifIndexes.empty())
	{
		checkIfState(index, parent);
	}
	
	ast::VisitableNode* node;
	if (nodeType.str().compare("send") == 0)
	{
		lastSend = index;
		node = makeSend(index, parent, line, statement, blkDepth, blkIndex);
	}
	else
	{
		node = makeNode(nodeType.str(), index, parent, line, statement, blkDepth, blkIndex);
	}

	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addValue(std::string val, int index, int parent, 
		int line, int statement, int blkDepth, int blkIndex)
{
	ast::BodyNode* node = makeNode(val, index, parent, line, statement, blkDepth, blkIndex);
	Builder::tree->addNode(node, parent);
	define = (val == "define");
}

void Builder::addNumber(std::string num, int index, 
		int parent, int line, int statement, int blkDepth, int blkIndex)
{
	float value = std::stof(num.c_str());
	ast::VisitableNode* node;
	if (remainder(value, 1) == 0)
	{
		node = makeInt((int)value, index, parent, line, statement, blkDepth, blkIndex);
	} 
	else
	{
		node = makeFloat(value, index, parent, line, statement, blkDepth, blkIndex);
	}

	Builder::tree->addNode(node, parent);
	define = false;
}

void Builder::addSymbol(std::string sym, int index,
		int parent, int line, int statement, int blkDepth, int blkIndex)
{
	ast::SymNode* node = makeSymbol(sym, index, parent, line, statement, blkDepth, blkIndex);
	Builder::tree->addNode(node, parent);

	// update last send if function name is being defined
	if (define)
	{
		ast::VisitableNode* send = Builder::tree->findNode(lastSend);
		send->accept(visitor, sym);
		define = false;
	}
}

void Builder::addIf(int index, int parent, int line, int statement, int blkDepth, int blkIndex)
{
	ast::IfNode* node = makeIf(index, parent, line, statement, blkDepth, blkIndex);
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
