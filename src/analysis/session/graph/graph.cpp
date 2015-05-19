#include "analysis/session/graph/graph.h"

namespace analysis
{

Graph::Graph()
{

}

void Graph::addBlock(analysis::SubGraph* sub)
{
	blocks.push_back(sub);
}

void Graph::addArc(int from, int to)
{
	arcs.insert(std::pair<int, int>(from, to));
}

int Graph::blockCount()
{
	return blocks.size();
}

} // namespace analysis