#include <iostream>
#include <ruby.h>

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "parse/ast/nodeTree.h"
#include "parse/ast/rootNode.h"
#include "parse/ast/bodyNode.h"

class Builder
{

private:
	
	ast::NodeTree* _tree;

public:
	Builder()
	{
		_tree = new ast::NodeTree();
	}

	~Builder()
	{
		delete _tree;
	}

	ast::BodyNode* makeNode(Rice::Symbol token, 
		int index, int parent)
	{
		return new ast::BodyNode(token.str(), index, parent);
	}

	void makeRoot(Rice::Symbol root)
	{
		ast::RootNode* rootNode = new ast::RootNode(root.str());
		_tree->setRoot(rootNode);
		std::cout << "\n";
	}

	void addNode(Rice::Symbol nodeType, int index, int parent)
	{
		ast::BodyNode* node = makeNode(nodeType.str(), index, parent);
		_tree->addNode(node, index, parent);
		std::cout << "\n";
	}

	void addValue(std::string val, int index, int parent)
	{
		ast::BodyNode* node = makeNode(val, index, parent);
		_tree->addNode(node, index, parent);
	}

};

extern "C"
void Init_builder()
{
	Rice::Data_Type<Builder> rb_cBuilder = 
		Rice::define_class<Builder>("Builder")
		.define_constructor(Rice::Constructor<Builder>())
		.define_method("makeRoot", &Builder::makeRoot)
		.define_method("addNode", &Builder::addNode)
		.define_method("addValue", &Builder::addValue);
}