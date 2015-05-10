#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

// persistant off by one error as statements index from 1
std::vector<analysis::TData*> PTrace::stats{ new TData() };
std::vector<std::string> PTrace::definedFuncs;
int PTrace::lastSet = 0;

PTrace::PTrace()
{
	int counter = Builder::tree->size();
	while (counter != 0)
	{
		stats.push_back(new TData());
		--counter;
	}

	std::cout << "Made Trace" << "\n";
}

PTrace::~PTrace()
{
	for (TData* data : stats)
	{
		delete data;
	}
}

void PTrace::setVT(float vt, int index)
{
	lastSet = index;
	std::cout << "Setting trace index " << index << " to " << vt << "\n";
	stats[index]->conVT = vt;
	stats[index]->cumVT = stats[index - 1]->cumVT + vt;
}

void PTrace::updateVT(int index)
{
	if (index > lastSet)
	{
		stats[index]->cumVT = stats[index - 1]->cumVT;
	}
}

void PTrace::createTrace(float conVT, int statement)
{
	setVT(conVT, statement);
}

void PTrace::createTrace(std::string func, int statement)
{
	std::cout << " create trace " << func
			<< " for statement " << statement;
}

void PTrace::createTrace(int statement)
{
	updateVT(statement);
}

float PTrace::vtAt(int index)
{
	return stats[index]->conVT;
}

float PTrace::cumVTAt(int index)
{
	std::cout << "Looking for index " << index << "\n";
	return stats[index]->cumVT;
}

float PTrace::totalVT()
{
	return stats[traceSize() - 1]->cumVT;
}

int PTrace::traceSize()
{
	return stats.size();
}

} // namespace analysis