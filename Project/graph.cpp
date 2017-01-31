#include "graph.h"
#include <algorithm>

Graph::Graph( const vector<Node*> & nodes, const vector<Edge> & edges) {
	addNodes(nodes);
	addEdges(edges);
}

Graph& Graph::addNode(Node * node) {
	m_nodes.push_back(node);
	return *this;
}

Graph& Graph::addEdge(Node * origin, Node * target) {
	origin->links_to.push_back(target);
	target->linked_from.push_back(origin);
	return *this;
}

Graph& Graph::addNodes(const vector<Node*> & nodes) {	
	m_nodes.reserve( size() + nodes.size() );
	m_nodes.insert( m_nodes.end(), nodes.begin(), nodes.end() );
	return *this;
}



Graph& Graph::addEdges(const vector<Edge> & edges) {
	for ( auto edge : edges ) {
        Node * source = edge.first;
        Node * target = edge.second;

        source->links_to.push_back(target);
        target->linked_from.push_back(source);
    }
	return *this;
}

Node * Graph::queryByNode(Node * node) const {
	auto found = find(m_nodes.begin(), m_nodes.end(), node);
	return found == m_nodes.end() ? nullptr : *found;
}


Node * Graph::queryByValue(const T& value, Node * preceded_by) {
	auto b = m_nodes.begin();
	auto e = m_nodes.end();

	if ( preceded_by != nullptr )
		b = find(b, e, preceded_by);
	
	while ( b != e )
		if ( (*b)->val == value )
			return *b;
	return nullptr;
}
