#include "analysis/pTrace.h"

#include "parse/builder.h"
#include "parse/ast/nodeTree.h"

namespace analysis
{

// persistant off by one error as statements index from 1
//std::vector<analysis::TData*> PTrace::stats{ new TData() };
//std::map<std::string, int> PTrace::defFuncs;
//std::vector<std::string> PTrace::definedFuncs;
//int PTrace::lastSet = 0;
//bool PTrace::inFunc = false;

// base tree construction
PTrace::PTrace()
{
	//stats{ new TData() }
	lastSet = 0;
	inFunc  = 0;
	lastStatement = -1;

	// persistant off by one error as statements index from 1
	int counter = Builder::tree->size() + 1;
	while (counter != 0)
	{
		stats.push_back(new TData());
		--counter;
	}

	std::cout << "======== Made Base Trace" << "\n";
}

// for tree specific construction
PTrace::PTrace(ast::NodeTree* tree)
{
	lastSet = 0;
	inFunc  = 0;
	lastStatement = -1;

	int counter = tree->size() + 1;
	std::cout << "Given tree size: " << counter << "\n";
	while (counter != 0)
	{
		stats.push_back(new TData());
		--counter;
	}
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
}

void PTrace::checkFunctionStatus(int statement)
{
	stats[statement]->setInFunc(isInFunc());
	std::map<int, bool> exists = Builder::getExitMap();

	for (auto it = exists.begin(); it != exists.end(); ++it)
	{
		if (it->first == statement)
		{
			stats[statement]->setInFunc(exists[statement]);
			std::cout << "setting " << statement << " to " << exists[statement] << "\n";
			setInFunc(exists[statement]);
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

void PTrace::setLast(int statement)
{
	lastStatement = statement;
}

int PTrace::getLast()
{
	return lastStatement;
}

float PTrace::getFunctionVT(std::string func)
{
	// need to use the base tree defined funcs list in all traces
	auto stats = (Builder::tree)->trace()->stats;
	int index  = (Builder::tree)->trace()->defFuncs[func];
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

void PTrace::traceSecondPass()
{
	bool first 	     = true;
	bool prevChange  = false;
	bool deadCode    = false;
	// bool updateIndex = false;
	int lastCumVT    = 0;

	for (int i = 1; i < traceSize(); ++i)
	{
		std::cout << " === InFor Pass Results ===\n";
		for (int i = 0; i < traceSize(); ++i)
		{
			std::cout << "Index " << i 
					<< " has VT " << stats[i]->conVT
					<< ", Current total: " << stats[i]->cumVT 
					<< " IN FUNC:: " << stats[i]->isInFunc()
					<< "\n";
		}
		std::cout << " === =================== ===\n";

		// if this is dead code, set it
		deadCode = (stats[i]->conVT == -3);

		// did we just leave a function?
		if ((stats[i - 1]->isInFunc() != stats[i]->isInFunc()))
		{
			// don't change things across blocks
			prevChange = false;
		}

		// updateIndex = (stats[i]->conVT == -1);
		
		if (prevChange)
		{
			stats[i]->cumVT = lastCumVT + stats[i]->conVT;
			lastCumVT = stats[i]->cumVT;
			// stats[i]->conVT = stats[i - 1]->conVT;
			// stats[i]->cumVT = stats[i - 1]->cumVT;
		}

		// is this index a method call?
		if (stats[i]->conVT == -1)
		{
			// code isn't dead
			deadCode = false;

			if (first)
			{
				stats[i]->conVT = 0;
				stats[i]->cumVT = 0;
				first = false;
			}

			// need to use the base tree defined funcs list in all traces
			auto defFuncs = (Builder::tree)->trace()->defFuncs;
			for (auto it = defFuncs.begin(); it != defFuncs.end(); ++it)
			{
				std::cout << it->first << " " << stats[i]->getFunc() << "\n";
				if (it->first == stats[i]->getFunc())
				{
					// float vtime = getFunctionVT(it->first);
					// stats[i]->conVT = stats[i]->conVT + vtime;
					// stats[i]->cumVT += vtime;
					// prevChange = true;
					float vtime = getFunctionVT(it->first);
					std::cout << vtime << "\n";
					stats[i]->conVT = stats[i]->conVT + vtime;
					stats[i]->cumVT += vtime;
					lastCumVT = stats[i]->cumVT;
					prevChange = true;
				}
			}
		}

		std::cout << "Index " << i
				<< " deadcode: " << deadCode
				<< " previous was dead? " << (stats[i - 1]->conVT == -3) << "\n";
				std::cout << "Last CumVT " << lastCumVT << "\n";
		// if this line is not dead code, if the previous line is, update some value
		if (!deadCode && (stats[i - 1]->conVT == -3))
		{
			stats[i]->cumVT = lastCumVT;
		}

		// track last cumulation
		if (!deadCode)
		{
			lastCumVT = stats[i]->cumVT;
		}
	}
}

} // namespace analysis