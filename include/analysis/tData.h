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

public:
	TData();

	float cumVT; // cumulative
	float conVT; // contribution

	void setFuncCall(bool b, std::string function);
	void setInFunc(bool b);

	bool isInFunc();
	std::string getFunc();
};

} // namespace analysis

#endif // __TDATA_H__