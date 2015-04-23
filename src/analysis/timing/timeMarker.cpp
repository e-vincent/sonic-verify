#include "analysis/timing/timeMarker.h"

TimeMarker::TimeMarker()
{
	_it = new ast::TreeIterator<ast::VisitableNode>(*(Builder::tree));
	std::cout << Builder::tree->rootNode << "\n";
}