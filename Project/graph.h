#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

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
    
    vector<Node*> nodes;

    Graph( const vector<Node*> & nodes = vector<Node*>(), 
            const vector<Edge> & edges = vector<Edge>() );

    Graph& addNode(Node * node);
    Graph& addEdge(Node * origin, Node * target);
};

#endif
