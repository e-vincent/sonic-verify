#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

float PTrace::vtCounter = 0;
int* PTrace::stats = NULL;

PTrace::PTrace()
{
	stats = new int[Builder::tree->size()];
	std::cout << "Made Trace" << "\n";
}

PTrace::~PTrace()
{
	delete[] stats;
}

void PTrace::test()
{
	std::cout << "\n" << "Success Test" << "\n";
}

void PTrace::setVT(float vt)
{
	PTrace::vtCounter += vt;
}

float PTrace::vT()
{
	return PTrace::vtCounter;
}

} // namespace analysis