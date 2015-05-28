#include "parse/ast/vTimeVisitor.h"

namespace ast
{
	
VTimeVisitor::VTimeVisitor()
{
	this->detectSleep = false;
	this->defineCall  = false;
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::BodyNode* bodyNode)
{
	// std::cout << "Visiting BodyNode " << bodyNode->value << "\n";
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
		trace->createTrace(bodyNode->statement(), bodyNode->isFuncCall(), bodyNode->value);
	}
	else
	{
		// carry forward the cumulative VT in the event 
		// we pass through begin/block nodes
		trace->createTrace(bodyNode->statement());
	}
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::IntNode* intNode)
{
	// std::cout << "Visiting IntNode " << intNode->val() << "\n";
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

	trace->createTrace(conVT, intNode->statement());
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::FloatNode* floatNode)
{
	// std::cout << "Visiting FloatNode " << floatNode->val() << "\n";
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

	trace->createTrace(conVT, floatNode->statement());
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::SymNode* symNode)
{
	// std::cout << "Visiting SymNode " << symNode->value << "\n";
	if (defineCall)
	{
		trace->createTrace(symNode->sym(), symNode->statement());
		defineCall = false;
	}
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::SendNode* sendNode)
{
	// std::cout << "Visiting SendNode " << sendNode->value << " " << sendNode->index << "\n";
	// std::cout << "    type " << sendNode->type() << "\n";
	// std::cout << "    func " << sendNode->func() << "\n";

	if (sendNode->type() == "function")
	{
		(trace->stats[sendNode->statement()])->setInFunc(true);
		(trace->stats[sendNode->statement()])->cumVT = 0; // start cumulation fresh with new func
		trace->setInFunc(true);
	}
}

void VTimeVisitor::visit(analysis::PTrace* trace, ast::IfNode* ifNode)
{
	// std::cout << "Visiting IfNode " << ifNode->index << " " << ifNode->statement() << "\n";
	// std::cout << "Left Index " << ifNode->getTrueIndex() 
	// 	<< " \nRight Index " << ifNode->getFalseIndex() << "\n";

	trace->createTrace(-2, ifNode->statement());
	trace->stats[ifNode->statement()]->setIfIndex(ifNode->index);
}

void VTimeVisitor::visit(ast::IfNode* ifNode, indexes& fill)
{
	// std::cout << ifNode->getTrueIndex() << " " << ifNode->getFalseIndex() << "\n"; 
	fill.trueIndex  = ifNode->getTrueIndex();
	fill.falseIndex = ifNode->getFalseIndex();
	// std::cout << "Fill1 " << fill.trueIndex << " " << fill.falseIndex << "\n";
}

} // namespace ast