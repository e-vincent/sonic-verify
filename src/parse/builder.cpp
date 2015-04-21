#include "parse/builder.h"

ast::NodeTree* Builder::tree = NULL;

Builder::Builder()
{
	Builder::tree = new ast::NodeTree();
}

Builder::~Builder()
{
	delete Builder::tree;
}

ast::BodyNode* Builder::makeNode(Rice::Symbol token, 
	int index, int parent)
{
	return new ast::BodyNode(token.str(), index, parent);
}

void Builder::makeRoot(Rice::Symbol root)
{
	ast::RootNode* rootNode = new ast::RootNode(root.str());
	Builder::tree->setRoot(rootNode);
}

void Builder::addNode(Rice::Symbol nodeType, int index, int parent)
{
	ast::BodyNode* node = makeNode(nodeType.str(), index, parent);
	Builder::tree->addNode(node, parent);
}

void Builder::addValue(std::string val, int index, int parent)
{
	ast::BodyNode* node = makeNode(val, index, parent);
	Builder::tree->addNode(node, parent);
}