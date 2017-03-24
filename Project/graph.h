#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

using std::vector;
using size_t = std::size_t;

//TODO:
//make 'T' and 'ID_T' template parameters
using T = int;
using ID_T = char;

class Node;
class Edge;
class Graph;

class Edge {
public: // !!! only for testing
    Node * origin;
    Node * target;

    int weight;

    friend class Graph;
};


class Node {
public: // !!! only for testing
    T value;

    ID_T    id;
    Graph * graph;

    vector<Edge*> links_to;
    vector<Edge*> linked_from;

    friend class Graph;
};


class Graph {

    vector<Node*> nodes;

public:
    Graph();
    //TODO:
    //add support for undirected graphs

    inline size_t size() const { return nodes.size(); }
    inline size_t isEmpty() const { return size() == 0; }

    //TODO:
    //generate an id when 'id' parammeter is ommited (hard to implement)
    Node * addNode(const T& value, const ID_T& id);

    Edge * addEdge(Node * origin, Node * target, int weight=1);
    Edge * addEdge(const ID_T & origin, const ID_T & target, int weight=1);

    Node * queryById(ID_T id) const ;

    Edge * queryByEdge(Node * origin, Node * target) const; 
    Edge * queryByEdge(const ID_T & origin, const ID_T & target) const;

    vector<Node *> queryByValue(const T& value) const;

    vector<vector<Edge*>> listPaths(Node * origin) const;
    vector<vector<Edge*>> listPaths(const ID_T & origin) const;


    void display(bool display_value = true, bool display_weight = true, std::ostream & out = std::cout) const;

    //TODO:
    //~Graph();
};

#endif
