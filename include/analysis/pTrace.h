#ifndef __PTRACE_H__
#define __PTRACE_H__

namespace analysis
{

class PTrace
{
private:
	static float vtCounter;

public:
	static int* stats;

	PTrace();
	~PTrace();

	static void test();
	static void setVT(float vt);
	static float vT();
};

} // namespace analysis

#endif // __PTRACE_H__