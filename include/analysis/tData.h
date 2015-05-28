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

public:
	TData();

	float cumVT; // cumulative
	float conVT; // contribution

	void setFuncCall(bool b, std::string function);
	void setInFunc(bool b);
	void setIfIndex(int index);

	bool isInFunc();
	std::string getFunc();
	int getIfIndex();
};

} // namespace analysis

#endif // __TDATA_H__