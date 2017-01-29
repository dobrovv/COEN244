#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <pair>

using T      = int;
using vector = std::vector;
using pair   = std::pair;


class Node {
    T val;
    vector<Node*> links_to;
    vector<Node*> linked_from;    
};


class Edge : public pair<Vertex *, Vertex *> {};


class Graph {
    
    vector<Node*> nodes;

    Graph( const vector<Node*> & nodes = vector<Node*>(), 
            const vector<Edge> & edges = vector<Edge>() );

    Graph& addNode(Node * node);
    Graph& addEdge(Node * origin, Node * target);


}

#endif
