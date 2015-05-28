#ifndef __PTRACE_H__
#define __PTRACE_H__

#include <vector>
#include <string>
#include <map>

#include "analysis/tData.h"
#include "parse/builder.h"
#include "parse/ast/nodeTree.h"
#include "parse/ast/vTimeVisitor.h"
#include "parse/ast/structs.h"

namespace ast
{ class NodeTree; }

namespace analysis
{

class PTrace
{
private:
	int lastSet;
	bool inFunc;
	int lastStatement; // detecting end of partial traces

public:
	std::vector<analysis::TData*> stats;
	std::map<std::string, int> defFuncs;
	std::vector<std::string> definedFuncs;
	std::vector<std::string> sessionTypes;

	PTrace();					 // base tree construction
	PTrace(ast::NodeTree* tree); // tree specific construction
	~PTrace();

	void initStats(int counter);
	void setVT(float vt, int index);
	void resolveIfs(ast::VTimeVisitor* visitor);
	void traceSecondPass();

	void createTrace(float conVT, int statement);		// TData with new VT
	void createTrace(std::string func, int statement);	// TData, func defined
	void createTrace(int statement);					// TData, carry previous VT
	void createTrace(int statement, bool funcCalled, std::string func);	// TData, func called

	void checkFunctionStatus(int statement);
	void setInFunc(bool b);

	float vtAt(int index);
	float cumVTAt(int index);
	float totalVT();
	int traceSize();
	bool isInFunc();

	void setLast(int statement);
	int getLast();
	float getFunctionVT(std::string func);
};

} // namespace analysis

#endif // __PTRACE_H__