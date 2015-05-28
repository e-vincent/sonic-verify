#ifndef __TIME_MARKER_H__
#define __TIME_MARKER_H__

#include <iostream>

#include "parse/builder.h"
#include "parse/treeIterator.h"
#include "parse/ast/vTimeVisitor.h"

#include "parse/ast/visitableNode.h"

#include "analysis/pTrace.h"

namespace ast
{

class TreeIterator; 
class NodeTree;
class VTimeVisitor;

} // namespace ast

namespace analysis
{

class TimeMarker
{
private:
	ast::TreeIterator* _it;

public:
	TimeMarker();

	void resolveIfs(analysis::PTrace* trace, ast::VTimeVisitor* visitor);
	void traceFirstPass(ast::NodeTree* tree, ast::VTimeVisitor* visitor, bool inIf);
};

} // namespace anlysis

#endif // __TIME_MARKER_H__