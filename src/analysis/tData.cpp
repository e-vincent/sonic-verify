#include "analysis/tData.h"

namespace analysis
{

TData::TData()
{
	cumVT = 0.0;
	conVT = 0.0;
	loopDepth = 0;
	funcCall  = false;
	funcFound = false;
}

} // namespace analysis