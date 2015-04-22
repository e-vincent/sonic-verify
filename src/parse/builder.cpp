#include "parse/builder.h"

ast::NodeTree<std::shared_ptr<ast::VisitableNode>>* Builder::tree = NULL;

Builder::Builder()
{
	Builder::tree = new ast::NodeTree<std::shared_ptr<ast::VisitableNode>>();
}

Builder::~Builder()
{
	delete Builder::tree;
}

std::shared_ptr<ast::BodyNode> Builder::makeNode(Rice::Symbol token, 
	int index, int parent)
{
	return std::shared_ptr<ast::BodyNode>(new ast::BodyNode(token.str(), index, parent));
}

void Builder::makeRoot(Rice::Symbol root)
{
	std::shared_ptr<ast::RootNode> rootNode(new ast::RootNode(root.str()));
	Builder::tree->setRoot(rootNode);
}

void Builder::addNode(Rice::Symbol nodeType, int index, int parent)
{
	// auto does => std::shared_ptr<ast::BodyNode> node = ...
	auto node = makeNode(nodeType.str(), index, parent);
	Builder::tree->addNode(node, parent);
}

void Builder::addValue(std::string val, int index, int parent)
{
	auto node = makeNode(val, index, parent);
	Builder::tree->addNode(node, parent);
}