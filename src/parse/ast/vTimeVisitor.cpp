#include "parse/ast/vTimeVisitor.h"

namespace ast
{
	
VTimeVisitor::VTimeVisitor()
{
	this->detectSleep = false;
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
		std::cout << "flip bool" << "\n";
		this->detectSleep = true;
	}

	if (bodyNode->isFuncCall())
	{
		std::cout << "Setting function call VT\n";
		analysis::PTrace::createTrace(bodyNode->statement(), bodyNode->isFuncCall());
	}
	else
	{
		// carry forward the cumulative VT in the event 
		// we pass through begin/block nodes
		analysis::PTrace::createTrace(bodyNode->statement());
		std::cout << "State: " << bodyNode->statement() << "\n";
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
		std::cout << "reset bool" << "\n";
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
		std::cout << "reset bool" << "\n";
	}		
	else
	{
		conVT = 0.0;
	}

	std::cout << "contributing " << conVT << "\n";
	analysis::PTrace::createTrace(conVT, floatNode->statement());
}

void VTimeVisitor::visit(ast::SymNode* symNode)
{
	std::cout << "Visiting SymNode " << symNode->value << "\n";
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