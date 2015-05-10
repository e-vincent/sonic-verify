#ifndef __TDATA_H__
#define __TDATA_H__

namespace analysis
{

class TData
{
private:
	bool funcCall; // this line is a function call
	bool funcFound; // the function called for has been defined
	bool inFunc;

public:
	TData();

	float cumVT; // cumulative
	float conVT; // contribution

	void setFuncCall(bool b);
	void setFuncFound(bool b);
	void setInFunc(bool b);

	bool isInFunc();
};

} // namespace analysis

#endif // __TDATA_H__