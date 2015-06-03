#ifndef __SG_ITERATOR_H__
#define __SG_ITERATOR_H__

#include <memory>

#include "analysis/session/graph/subGraph.h"
#include "analysis/session/graph/nodes/nodes.h"

namespace graph
{

class SubGraph;

class SGIterator
{
private:
	graph::SubGraph& _graph;
	std::list<graph::GraphNode*>::iterator iterator;

public:
	SGIterator(graph::SubGraph& graph);
	SGIterator(graph::SubGraph& graph, bool);

	SGIterator operator++();
	SGIterator operator++(int);
	bool operator==(const SGIterator& rhs);
	bool operator!=(const SGIterator& rhs);

	graph::GraphNode& operator*();
	const graph::GraphNode& operator*() const;
};

} // namespae graph

#endif // __SG_ITERATOR_H__