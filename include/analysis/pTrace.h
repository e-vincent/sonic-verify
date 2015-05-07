#ifndef __PTRACE_H__
#define __PTRACE_H__

namespace analysis
{

class PTrace
{
public:
	int* stats;

	PTrace();
	~PTrace();
};

} // namespace analysis

#endif // __PTRACE_H__