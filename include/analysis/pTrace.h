#ifndef __PTRACE_H__
#define __PTRACE_H__

#include <vector>
#include <string>
#include <map>

#include "analysis/tData.h"
#include "parse/builder.h"

namespace analysis
{

class PTrace
{
private:
	static int lastSet;
	//static std::map<int, bool> defines;
	static bool inFunc;

public:
	static std::vector<analysis::TData*> stats;
	static std::map<std::string, int> defFuncs;
	static std::vector<std::string> definedFuncs;

	PTrace();
	~PTrace();

	static void setVT(float vt, int index);

	static void createTrace(float conVT, int statement);		// TData with new VT
	static void createTrace(std::string func, int statement);	// TData, func defined
	static void createTrace(int statement);						// TData, carry previous VT
	static void createTrace(int statement, bool funcCalled, std::string func);	// TData, func called

	static void checkFunctionStatus(int statement);
	static void setInFunc(bool b);

	static float vtAt(int index);
	static float cumVTAt(int index);
	static float totalVT();
	static int traceSize();
	static bool isInFunc();
	static float getFunctionVT(std::string func);

	static void updateTraceWithFuncVTs();
};

} // namespace analysis

#endif // __PTRACE_H__