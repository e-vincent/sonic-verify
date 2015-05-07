#include "analysis/timing/timeMarker.h"
#include "analysis/pTrace.h"

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

		// Go forth and adapt an IterateVisitor
	// which will do the int detecting for you
	// detect sleep sends as a flag to count time
	// check statements are recording properly
	// and then time at given statement can be recorded

	// maybe stick line number in there somehow
	// prog trace of objects for all the best information

	std::cout << "OUT OF LOOP" << "\n";
}

} // namespace analysis