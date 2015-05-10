#include "analysis/tData.h"

namespace analysis
{

TData::TData()
{
	cumVT = 0.0;
	conVT = 0.0;
	funcCall  = false;
	funcFound = false;
	inFunc	  = false;
}

void TData::setFuncCall(bool b)
{
	funcCall = b;
}

void TData::setFuncFound(bool b)
{
	funcFound = b;
}

void TData::setInFunc(bool b)
{
	inFunc = b;
}

bool TData::isInFunc()
{
	return inFunc;
}

} // namespace analysis