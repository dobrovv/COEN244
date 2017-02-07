#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

//TODO:
//make 'T' and 'ID_T' template parameters
using T = int;
using ID_T = int;

using size_t = std::size_t;


class Node;
class Graph;
class Edge;


class Edge {
    Node * origin;
    Node * target;

    int weight;

    friend class Graph;
};


class Node {
    T value;

    ID_T    id;
    Graph * graph;

    std::vector<Edge*> links_to;
    std::vector<Edge*> linked_from;

    friend class Graph;
};


class Graph {

    std::vector<Node*> nodes;

public:
    Graph();
    //TODO:
    //add support for undirected graphs

	inline size_t size() const { return nodes.size(); }
	inline size_t isEmpty() const { return size() == 0; }

    //TODO:
    //generate an id when 'id' parammeter is ommited
    Node * addNode(const T& value, const ID_T& id);
    Edge * addEdge(Node * origin, Node * target, int weight=1);
    Edge * addEdge(const ID_T& origin, const ID_T& target, int weight=1);

    Node * queryById(ID_T id) const ;
    //TODO:
    //Node * queryByEdge(Node * origin, Node * target);
    //Node * queryByEdge(ID_T origin, ID_T target);
    //6. given a starting vertex, list the paths this vertex leads to. 
	
    std::vector<Node *> queryByValue(const T& value) const;

    void display(bool display_value = true, bool display_weight = true, std::ostream & out = std::cout) const;

    //TODO:
    //~Graph();
    
    
    
};

#endif
