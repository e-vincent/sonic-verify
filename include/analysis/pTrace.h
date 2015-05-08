#ifndef __PTRACE_H__
#define __PTRACE_H__

#include <vector>

#include "analysis/tData.h"

namespace analysis
{

class PTrace
{
private:

public:
	//static std::vector<int*> stats;
	static std::vector<analysis::TData*> stats;

	PTrace();
	~PTrace();

	static void setVT(float vt, int index);
	static float vtAt(int index);
	static float cumVTAt(int index);
	static float totalVT();
	static int traceSize();
};

} // namespace analysis

#endif // __PTRACE_H__