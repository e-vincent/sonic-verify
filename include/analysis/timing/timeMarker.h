#ifndef __TIME_MARKER_H__
#define __TIME_MARKER_H__

#include <iostream>

#include "parse/builder.h"
#include "parse/treeIterator.h"
#include "parse/ast/vTimeVisitor.h"

#include "parse/ast/nodes/visitableNode.h"

#include "analysis/pTrace.h"

namespace analysis
{

class TimeMarker
{
private:
	ast::TreeIterator* _it;

public:
	TimeMarker();
};

} // namespace anlysis

#endif // __TIME_MARKER_H__