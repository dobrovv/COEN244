#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <stdexcept>

/*Type aliases to standart library*/

using std::size_t;

using std::vector;
using std::ostream;
using std::exception;

/*Graph's Exeptions*/

class invalid_id: exception {
    const char * what() const noexcept override
    { return "Deault constructed or nonpresent id used as a parameter"; } 
};

class invalid_node: exception {
    const char * what() const noexcept override 
    { return "Node isn't present in the graph"; } 
};


//TODO:
//make 'T' and 'ID_T' template parameters
using T = int;
using ID_T = char;

class Node;
class Edge;
class Graph;

class Node {
    T value;

    ID_T    id;
    Graph * graph;

    vector<Edge*> links_to; // stores Edges that go from "this" node to "target" node
    vector<Edge*> linked_from; // stores Edges that go from "target" node to "this" node

protected:
    Node(T value, ID_T id, Graph *graph)
        : value(value), id(id), graph(graph), links_to(), linked_from() 
    {};
    ~Node() {}; 
    
    friend class Graph;

public:
    T getValue() const { return value; }
    ID_T getID() const { return id; }
    Graph * getGraph() const { return graph; }

    vector<Edge*> edgesToNode() const { return linked_from; }
    vector<Edge*> edgesFromNode() const { return links_to; }

    void setValue(const T & newValue) { value=newValue; }
    
};


class Edge {
    Node * origin;
    Node * target;

    int weight;

protected:
    Edge(Node * origin, Node * target, int weight)
        : origin(origin), target(target), weight(weight)
    {};
    ~Edge() {};

    friend class Graph;

public:
    Node * getOrigin() const { return origin; }
    Node * getTarget() const { return target; }
    int getWeight() const { return weight; }

    void setWeight( int newWeight) { weight=newWeight;}
};


class Graph {

    vector<Node*> nodes;

public:
    Graph();
    ~Graph();
    Graph(const Graph& other);

    /* Member Access Functions*/
    inline size_t size() const { return nodes.size(); }
    inline size_t isEmpty() const { return size() == 0; }

    Node * addNode(const T& value, const ID_T& id);    
    void removeNode(Node * node);


    Edge * addEdge(Node * origin, Node * target, int weight=1);
    Edge * addEdge(const ID_T & origin, const ID_T & target, int weight=1);
    void removeEdge(Edge * edge);
    
    vector<Node*> getNodes() const;
    vector<Edge*> getEdges() const;
   
    // Functions returning paths followed from a specific node
    vector<vector<Edge*>> listPaths(Node * origin) const;
    vector<vector<Edge*>> listPaths(const ID_T & origin) const;

    Node * operator[](const ID_T & id);

    /* Quering Functions */
    Node * queryById(ID_T id) const ;
    Edge * queryByEdge(Node * origin, Node * target) const; 
    Edge * queryByEdge(const ID_T & origin, const ID_T & target) const;

    // Functions returtning wheter there exists a path between
    // the origin and target node
    bool leadsTo(Node * origin, Node * target) const;
    bool leadsTo(ID_T origin, ID_T target) const;

    vector<Node *> queryByValue(const T& value) const;

        
    void displayEdges(bool display_value = true, bool display_weight = true, std::ostream & out = std::cout) const;

};

/* Helper & Miscellaneous Functions */
    
// removes an element by value from a generic vector
template <typename ELEM_T>
bool removeElement(vector<ELEM_T> & vec, ELEM_T elem);


ostream & operator<<(ostream& out, Node * node);
ostream & operator<<(ostream& out, Edge *edge);
ostream & operator<<(ostream & out, const Graph &);

#endif
