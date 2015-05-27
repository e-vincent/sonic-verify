#ifndef __TYPE_VISITOR_H__
#define __TYPE_VISITOR_H__

#include "analysis/session/graph/iVisitor.h"

namespace analysis
{

class TypeVisitor : public analysis::IVisitor
{
public:
	TypeVisitor();

	~TypeVisitor() {}

	virtual void visit(graph::CueNode* cueNode) override;
	virtual void visit(graph::SyncNode* syncNode) override;
};

} // namespace analysis

#endif // __TYPE_VISITOR_H__