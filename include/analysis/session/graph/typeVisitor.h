#ifndef __TYPE_VISITOR_H__
#define __TYPE_VISITOR_H__

#include "analysis/session/graph/iVisitor.h"

namespace analysis
{

class TypeVisitor : public analysis::IVisitor
{
public:
	TypeVisitor();

	virtual void visit(graph::GraphNode* graphNode);
	virtual void visit(graph::CueNode* cueNode);
	virtual void visit(graph::SyncNode* syncNode);
};

} // analysis

#endif // __TYPE_VISITOR_H__