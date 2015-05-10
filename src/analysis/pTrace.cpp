#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

// persistant off by one error as statements index from 1
std::vector<analysis::TData*> PTrace::stats{ new TData() };
std::vector<std::string> PTrace::definedFuncs;
int PTrace::lastSet = 0;
bool PTrace::inFunc = false;

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
	if (index != 0)
	{
		stats[index]->cumVT = stats[index - 1]->cumVT + vt;
	}
}

void PTrace::updateVT(int index)
{
	std::cout << "UpdateVT " << index << "\n";
	// if (index > lastSet)
	// {
	// 	stats[index]->cumVT = stats[index - 1]->cumVT;
	// }
}

void PTrace::createTrace(float conVT, int statement)
{
	stats[statement]->setInFunc(isInFunc());
	setVT(conVT, statement);
}

void PTrace::createTrace(std::string func, int statement)
{
	stats[statement]->setInFunc(isInFunc());
	std::cout << " create trace " << func
			<< " for statement " << statement;
}

void PTrace::createTrace(int statement)
{
	stats[statement]->setInFunc(isInFunc());
	updateVT(statement);
}

void PTrace::createTrace(int statement, bool funcCalled)
{
	stats[statement]->setInFunc(isInFunc());
	stats[statement]->setFuncCall(funcCalled);
	stats[statement]->setFuncFound(!funcCalled);
	// -1 will signal the program to re-calculate numbers on second run
	setVT(-1, statement);
}

void PTrace::setInFunc(bool b)
{
	inFunc = b;
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

bool PTrace::isInFunc()
{
	return inFunc;
}

} // namespace analysis