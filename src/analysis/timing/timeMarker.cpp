#include "analysis/timing/timeMarker.h"

namespace analysis
{

TimeMarker::TimeMarker()
{
	// given how the constructor works, null check should really be done here
	if (!(Builder::tree))
	{
		std::cout << "tree hasn't initialized properly" << "\n";
	}

	_it = new ast::TreeIterator(*(Builder::tree), (Builder::tree)->root());
	ast::VTimeVisitor* visitor = new ast::VTimeVisitor();
	new analysis::PTrace();

	ast::TreeIterator start = Builder::tree->begin();
	ast::TreeIterator end   = Builder::tree->end();
	for (ast::TreeIterator it = start; it != end; ++it)
	{
		(&(*it))->accept(visitor);
	}

	std::cout << "End VT: " << analysis::PTrace::totalVT() << "\n";
	for (int i = 0; i < analysis::PTrace::traceSize(); ++i)
	{
		std::cout << "Index " << i 
				<< " has VT " << PTrace::stats[i]->conVT
				<< ", Current total: " << PTrace::stats[i]->cumVT 
				<< " IN FUNC:: " << PTrace::stats[i]->isInFunc()
				<< "\n";
	}

	std::cout << "OUT OF LOOP" << "\n";
}

} // namespace analysis