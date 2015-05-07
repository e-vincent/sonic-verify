#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

PTrace::PTrace()
{
	stats = new int[Builder::tree->size()];
}

PTrace::~PTrace()
{
	delete[] stats;
}

} // namespace analysis