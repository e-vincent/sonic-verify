#include "analysis/session/graph/sgIterator.h"

namespace graph
{

SGIterator::SGIterator(graph::SubGraph& graph)
	: _graph(graph)
{
	iterator = graph.nodes.begin();
}

SGIterator::SGIterator(graph::SubGraph& graph, bool)
	: _graph(graph)
{
	iterator = graph.nodes.end();	
}

SGIterator SGIterator::operator++()
{
	++iterator;
	return *this;
}

SGIterator SGIterator::operator++(int)
{
	SGIterator clone(*this);
	++iterator;
	return clone;
}

bool SGIterator::operator==(const SGIterator& rhs)
{
	return this->iterator == rhs.iterator;
}

bool SGIterator::operator!=(const SGIterator& rhs)
{
	return !(*this == rhs);
}

graph::GraphNode& SGIterator::operator*()
{
	return *(*this->iterator);
}

const graph::GraphNode& SGIterator::operator*() const
{
	return **iterator;
}

} // namespace graph