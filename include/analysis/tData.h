#ifndef __TDATA_H__
#define __TDATA_H__

#include <string>

namespace analysis
{

class TData
{
private:
	bool funcCall; 		// this line is a function call
	std::string func; 	// function called
	bool inFunc;
	int ifIndex;
	int blkIndex;

public:
	TData();

	float cumVT; // cumulative
	float conVT; // contribution
	int line;

	void setFuncCall(bool b, std::string function);
	void setInFunc(bool b);
	void setIfIndex(int index);
	void setBlkParent(int index);

	bool isInFunc();
	std::string getFunc();
	int getIfIndex();
	int blkParent();
};

} // namespace analysis

#endif // __TDATA_H__