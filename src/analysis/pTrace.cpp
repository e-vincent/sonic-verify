#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

// persistant off by one error as statements index from 1
std::vector<analysis::TData*> PTrace::stats{ new TData() };

PTrace::PTrace()
{
	int counter = Builder::tree->size();
	while (counter != 0)
	{
		PTrace::stats.push_back(new TData());
		--counter;
	}

	for (auto s : PTrace::stats)
	{
		std::printf("%p\n", s);
	}

	std::cout << "Made Trace" << "\n";
}

PTrace::~PTrace()
{
	for (TData* data : PTrace::stats)
	{
		delete data;
	}
}

void PTrace::setVT(float vt, int index)
{
	std::cout << "Setting trace index " << index << " to " << vt << "\n";
	PTrace::stats[index]->conVT = vt;
	PTrace::stats[index]->cumVT = PTrace::stats[index - 1]->cumVT + vt;
}

float PTrace::vtAt(int index)
{
	return PTrace::stats[index]->conVT;
}

float PTrace::cumVTAt(int index)
{
	std::cout << "Looking for index " << index << "\n";
	return PTrace::stats[index]->cumVT;
}

float PTrace::totalVT()
{
	return PTrace::stats[traceSize() - 1]->cumVT;
}

int PTrace::traceSize()
{
	return PTrace::stats.size();
}

} // namespace analysis