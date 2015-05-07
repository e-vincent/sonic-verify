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

	ast::TreeIterator start = Builder::tree->begin();
	ast::TreeIterator end   = Builder::tree->end();

	ast::VTimeVisitor* visitor = new ast::VTimeVisitor();

	for (ast::TreeIterator it = start; it != end; ++it)
	{
		std::cout << "Statement " << (*it).statement() << "\n";
		std::cout << "Current Line: " << (*it).line() << ": ";
		std::cout << (*it).value;
		std::cout << "\n";

		visitor->visit(*it);
	// Go forth and adapt an IterateVisitor
	// which will do the int detecting for you
	// detect sleep sends as a flag to count time
	// check statements are recording properly
	// and then time at given statement can be recorded

	// maybe stick line number in there somehow
	// prog trace of objects for all the best information


		if (((*it).value) == ("int"))
		{
			std::cout << "int found" << "\n";
			// define visitors to see values
			//std::cout << node.val();
		} 
	}

	std::cout << "OUT OF LOOP" << "\n";
}

} // namespace analysis