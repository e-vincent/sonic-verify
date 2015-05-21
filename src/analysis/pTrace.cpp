#include "analysis/pTrace.h"

#include "parse/builder.h"

namespace analysis
{

// persistant off by one error as statements index from 1
std::vector<analysis::TData*> PTrace::stats{ new TData() };
std::map<std::string, int> PTrace::defFuncs;
std::vector<std::string> PTrace::definedFuncs;
std::vector<std::string> sessionTypes;

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

	std::cout << "======== Made Trace" << "\n";
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

// TData with new VT
void PTrace::createTrace(float conVT, int statement)
{
	std::cout << "checkFunction from newVT Trace\n";
	checkFunctionStatus(statement);
	setVT(conVT, statement);
}

// TData, func defined
void PTrace::createTrace(std::string func, int statement)
{
	std::cout << "checkFunction from funcDefined Trace\n";
	checkFunctionStatus(statement);

	std::cout << " <= Can Define " << func << " " << statement << "here\n";
	defFuncs.insert(std::pair<std::string, int> (func, statement));
}

// TData, carry previous VT
void PTrace::createTrace(int statement)
{
	std::cout << "checkFunction from previousVT Trace\n";
	checkFunctionStatus(statement);
}

// TData, func called
void PTrace::createTrace(int statement, bool funcCalled, std::string func)
{
	// std::cout << "state " << statement 
	// 	<< " where function is " << funcCalled << "\n";
	stats[statement]->setInFunc(isInFunc());
	stats[statement]->setFuncCall(funcCalled, func);
	// -1 will signal the program to re-calculate numbers on second run
	setVT(-1, statement);
	std::cout << "TRACE CREATION FOR " << func << "\n";
}

void PTrace::checkFunctionStatus(int statement)
{
	std::cout << "Are we in a function? " << isInFunc() << "\n";
	stats[statement]->setInFunc(isInFunc());
	std::map<int, bool> exits = Builder::getExitMap();

	for (auto it = exits.begin(); it != exits.end(); ++it)
	{
		if (it->first == statement)
		{
			stats[statement]->setInFunc(exits[statement]);
			std::cout << "setting " << statement << " to " << exits[statement] << "\n";
			setInFunc(exits[statement]);
		}
	}
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

float PTrace::getFunctionVT(std::string func)
{
	int index = defFuncs[func];
	float result = 0.0;

	for (int i = index; i < traceSize(); ++i)
	{
		if (stats[i]->isInFunc())
		{
			result += stats[i]->conVT;
		}
		else
		{
			break;
		}
	}

	return result;
}

void PTrace::updateTraceWithFuncVTs()
{
	bool prevChange  = false;
	bool first 		 = true;
	bool updateIndex = false;
	for (int i = 0; i < traceSize(); ++i)
	{
		// index 0 is always out of function and would break the logic
		if (i > 1 && (stats[i - 1]->isInFunc() != stats[i]->isInFunc()))
		{
			// don't change things across blocks
			prevChange = false;
		}

		updateIndex = (stats[i]->conVT == -1);
		
		if (prevChange)
		{
			stats[i]->conVT = stats[i - 1]->conVT;
			stats[i]->cumVT = stats[i - 1]->cumVT;
		}

		if (updateIndex)
		{
			if (first)
			{
				stats[i]->conVT = 0;
				stats[i]->cumVT = 0;
				first = false;
			}

			for (auto it = defFuncs.begin(); it != defFuncs.end(); ++it)
			{
				if (it->first == stats[i]->getFunc())
				{
					float vtime = getFunctionVT(it->first);
					stats[i]->conVT = stats[i]->conVT + vtime;
					stats[i]->cumVT += vtime;
					prevChange = true;
				}
			}
		}
	}
}

} // namespace analysis