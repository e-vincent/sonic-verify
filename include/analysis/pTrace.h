#ifndef __PTRACE_H__
#define __PTRACE_H__

#include <vector>
#include <string>

#include "analysis/tData.h"

namespace analysis
{

class PTrace
{
private:
	static int lastSet;

public:
	static std::vector<analysis::TData*> stats;
	static std::vector<std::string> definedFuncs;

	PTrace();
	~PTrace();

	static void setVT(float vt, int index);
	static void updateVT(int index);

	static void createTrace(float conVT, int statement);
	static void createTrace(std::string func, int statement);
	static void createTrace(int statement);

	static float vtAt(int index);
	static float cumVTAt(int index);
	static float totalVT();
	static int traceSize();
};

} // namespace analysis

#endif // __PTRACE_H__