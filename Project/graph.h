#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

using size_t = std::size_t;
using T      = int;
template<typename T> 
using vector = std::vector<T>;
template<typename T1, typename T2> 
using pair   = std::pair<T1,T2>;


class Node {
    T val;
    vector<Node*> links_to;
    vector<Node*> linked_from;
    friend class Graph;
};


class Edge : public pair<Node *, Node *> {};


class Graph {
    
    vector<Node*> m_nodes;

public:
    Graph( const vector<Node*> & nodes = vector<Node*>(), 
            const vector<Edge> & edges = vector<Edge>() );

	inline size_t size() const
		{ return m_nodes.size(); }

	inline size_t isEmpty() const
		{ return size() == 0; }

    Graph& addNode(Node * node);
    Graph& addEdge(Node * origin, Node * target);
	
	inline Graph& addEdge(const Edge & edge) 
		{ return addEdge(edge.first, edge.second); }
	
	Graph& addNodes(const vector<Node*> & nodes);
	Graph& addEdges(const vector<Edge> & edges);

	
	Node * queryByNode(Node * node) const;
	Node * queryByValue(const T& value, Node * preceded_by = nullptr);
};

#endif
