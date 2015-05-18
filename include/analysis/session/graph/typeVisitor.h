#ifndef __TYPE_VISITOR_H__
#define __TYPE_VISITOR_H__

#include "analysis/session/graph/iVisitor.h"

namespace analysis
{

class TypeVisitor : public analysis::IVisitor
{
public:
	TypeVisitor();

	virtual void visit(analysis::GraphNode* cueNode);
	virtual void visit(analysis::CueNode* cueNode);
	virtual void visit(analysis::SyncNode* syncNode);
};

} // analysis

#endif // __TYPE_VISITOR_H__