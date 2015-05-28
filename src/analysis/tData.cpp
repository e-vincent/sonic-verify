#include "analysis/tData.h"

namespace analysis
{

TData::TData()
{
	cumVT = 0.0;
	conVT = 0.0;
	funcCall  = false;
	inFunc	  = false;
	ifIndex	  = -1;
}

void TData::setFuncCall(bool b, std::string function)
{
	funcCall = b;
	func = function;
}

void TData::setInFunc(bool b)
{
	inFunc = b;
}

void TData::setIfIndex(int index)
{
	ifIndex = index;
}

bool TData::isInFunc()
{
	return inFunc;
}

std::string TData::getFunc()
{
	return func;
}

int TData::getIfIndex()
{
	return ifIndex;
}

} // namespace analysis