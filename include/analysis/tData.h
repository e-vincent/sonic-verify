#ifndef __TDATA_H__
#define __TDATA_H__

namespace analysis
{

class TData
{
private:
	bool funcCall;
	bool funcFound;

public:
	TData();

	int loopDepth;
	float cumVT; // cumulative
	float conVT; // contribution
};

} // namespace analysis

#endif // __TDATA_H__