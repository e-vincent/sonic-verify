#include "parse/ast/vTimeVisitor.h"

namespace ast
{
	
VTimeVisitor::VTimeVisitor()
{
	this->detectSleep = false;
	this->defineCall  = false;
}

void VTimeVisitor::visit(ast::RootNode* rootNode)
{
	std::cout << "Visiting Root " << rootNode->value << "\n";
}

void VTimeVisitor::visit(ast::BodyNode* bodyNode)
{
	std::cout << "Visiting BodyNode " << bodyNode->value << "\n";
	if ("sleep" == bodyNode->value)
	{
		this->detectSleep = true;
	}
	else if ("define" == bodyNode->value)
	{
		this->defineCall  = true;
	}

	if (bodyNode->isFuncCall())
	{
		analysis::PTrace::createTrace(bodyNode->statement(), bodyNode->isFuncCall(), bodyNode->value);
	}
	else
	{
		// carry forward the cumulative VT in the event 
		// we pass through begin/block nodes
		analysis::PTrace::createTrace(bodyNode->statement());
	}
}

void VTimeVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";
	float conVT;

	if (this->detectSleep)
	{
		conVT = (float) intNode->val();
		this->detectSleep = false;
	}		
	else
	{
		conVT = 0.0;
	}

	analysis::PTrace::createTrace(conVT, intNode->statement());
}

void VTimeVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting FloatNode " << floatNode->val() << "\n";
	float conVT;

	if (this->detectSleep)
	{
		conVT = floatNode->val();
		this->detectSleep = false;
	}		
	else
	{
		conVT = 0.0;
	}

	analysis::PTrace::createTrace(conVT, floatNode->statement());
}

void VTimeVisitor::visit(ast::SymNode* symNode)
{
	std::cout << "Visiting SymNode " << symNode->value << "\n";
	if (defineCall)
	{
		analysis::PTrace::createTrace(symNode->sym(), symNode->statement());
		defineCall = false;
	}
}

void VTimeVisitor::visit(ast::SendNode* sendNode)
{
	std::cout << "Visiting SendNode " << sendNode->value << " " << sendNode->index << "\n";
	std::cout << "    type " << sendNode->type() << "\n";
	std::cout << "    func " << sendNode->func() << "\n";

	if (sendNode->type() == "function")
	{
		(analysis::PTrace::stats[sendNode->statement()])->setInFunc(true);
		(analysis::PTrace::stats[sendNode->statement()])->cumVT = 0; // start cumulation fresh with new func
		analysis::PTrace::setInFunc(true);
	}
}

} // namespace ast