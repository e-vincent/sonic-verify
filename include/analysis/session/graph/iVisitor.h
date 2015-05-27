#ifndef __ANALYSIS_IVISITOR_H__
#define __ANALYSIS_IVISITOR_H__

#include <iostream>

#include "analysis/session/graph/nodes/nodes.h"

namespace analysis
{

class IVisitor
{
public:

	IVisitor() = default;
	virtual ~IVisitor() {}

	virtual void visit(graph::CueNode* cueNode) = 0;
	virtual void visit(graph::SyncNode* syncNode) = 0;
};

} // namespace ast

#endif // __ANALYSIS_IVISITOR_H__