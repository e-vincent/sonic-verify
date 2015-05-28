#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <iostream>
#include <iterator>
#include <memory>

#include "parse/treeIterator.h"
#include "parse/ast/visitableNode.h"
#include "analysis/pTrace.h"

namespace analysis
{ class PTrace; }

namespace ast
{

// forward declaration
class TreeIterator;

class NodeTree
{
private:
	analysis::PTrace* treeTrace;
	int treeSize;
	int lines;

public:
	typedef TreeIterator iterator;

	ast::VisitableNode* rootNode;

	NodeTree();
	NodeTree(ast::VisitableNode* root, int parentSize);
	~NodeTree();

	void setUpTrace();

	TreeIterator begin();
	TreeIterator end();

	ast::VisitableNode* root();
	ast::VisitableNode* findNode(int index);
	ast::VisitableNode* findNext(ast::VisitableNode* node);

	void setRoot(ast::VisitableNode* rootNode);
	void addNode(ast::VisitableNode* node, int parent);

	analysis::PTrace* trace();

	void setSize(int size);
	int size();
	void setLineCount(int count);
	int lineCount();
};

// inline std::ostream& operator<<(std::ostream& stream, const NodeTree&)
// {
// 	stream << "Not implemented\n";
// 	return stream;
// }


} // ast

#endif // __NODE_TREE_H__