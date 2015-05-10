#include "parse/ast/bodyNode.h"
#include "parse/ast/vTimeVisitor.h"

namespace ast
{

BodyNode::BodyNode(std::string symbol, int index, int parent, int line, int statement, int blkDepth)
: ast::VisitableNode(index, parent, line, statement, blkDepth)
{
	this->value = symbol;
}

void BodyNode::accept(VTimeVisitor* v)
{
	v->visit(this);
}

bool BodyNode::isFuncCall()
{
	std::cout << "=========\n";
	std::cout << "\n Current value: " << this->value << "\n";

	std::cout << (this->value.compare("sleep") != 0) << "\n";
	std::cout << (this->value.compare("play") != 0) << "\n";
	std::cout << (this->value.compare("define") != 0) << "\n";
	std::cout << (this->value.compare("loop") != 0) << "\n";
	std::cout << (this->value.compare("live_loop") != 0) << "\n";
	std::cout << (this->value.compare("in_thread") != 0) << "\n";
	std::cout << !(this->value.empty()) << "\n";

	std::cout << "=========\n";
	return (this->value.compare("sleep") != 0 
			&& this->value.compare("play") != 0
			&& this->value.compare("define") != 0
			&& this->value.compare("loop") != 0
			&& this->value.compare("live_loop") != 0
			&& this->value.compare("in_thread") != 0
			&& this->value.compare("sample") != 0
			&& this->value.compare("block") != 0
			&& this->value.compare("begin") != 0
			&& this->value.compare("args") != 0
			&& !(this->value.empty()));
}

} // namespace ast