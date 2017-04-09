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

class invalid_node: exception {
    const char * what() const noexcept override 
    { return "Invalid Node reference used as a parameter"; } 
};

class invalid_id: exception {
    const char * what() const noexcept override
    { return "Deault constructed or nonpresent id used as a parameter"; } 
};


/* Class Declarations */

template< typename T, typename ID_T> class Node;
template< typename T, typename ID_T> class Edge;
template< typename T, typename ID_T> class Graph;


/* Helper & Miscellaneous Functions */
    
// removes an element by value from a generic vector
template <typename ELEM_T>
bool removeElement(vector<ELEM_T> & vec, ELEM_T elem);

// ostream overloads for Classes
template <typename T, typename ID_T>
ostream & operator<<(ostream& out, Node<T,ID_T> * node);

template <typename T, typename ID_T>
ostream & operator<<(ostream& out, Edge<T,ID_T> *edge);

template <typename T, typename ID_T>
ostream & operator<<(ostream & out, const Graph<T,ID_T> & g);

/* Class Definitions */

template <typename T, typename ID_T>
class Node {
    using EdgeT  = Edge<T,ID_T>;
    using GraphT = Graph<T, ID_T>;

private:
    T value;

    ID_T    id;
    GraphT * graph;

    vector<EdgeT*> links_to; // stores Edges that go from "this" node to "target" node
    vector<EdgeT*> linked_from; // stores Edges that go from "target" node to "this" node

private:
    Node(T value, ID_T id, GraphT *graph)
        : value(value), id(id), graph(graph), links_to(), linked_from() 
    {};
    ~Node() {}; 
    
    friend GraphT; // the class Graph<T, ID_T> is declared as a friend of Node 
                   // to access the constructor 

public:
    T getValue() const { return value; }
    void setValue(const T & newValue) { value=newValue; }
    
    ID_T getID() const { return id; }
    GraphT * getGraph() const { return graph; }

    vector<EdgeT*> edgesToNode() const { return linked_from; }
    vector<EdgeT*> edgesFromNode() const { return links_to; }
    
    vector<EdgeT*> edgesUndirected() const 
    {
        vector<EdgeT*> undirected_edges(links_to);
        undirected_edges.insert( undirected_edges.end(), linked_from.begin(), linked_from.end() );
        return undirected_edges;
    } 
};


template <typename T, typename ID_T>
class Edge {
    using NodeT  = Node<T, ID_T>;
    using GraphT = Graph<T, ID_T>;

    NodeT * origin;
    NodeT * target;

    int weight;

private:
    Edge(NodeT * origin, NodeT * target, int weight)
        : origin(origin), target(target), weight(weight)
    {};
    ~Edge() {};

    friend GraphT; // the class Graph<T, ID_T> is declared as a friend of Edge
                   // to access the constructor 


public:
    NodeT * getOrigin() const { return origin; }
    NodeT * getTarget() const { return target; }
    int getWeight() const { return weight; }

    void setWeight( int newWeight) { weight=newWeight;}
};

template <typename T, typename ID_T>
class Graph {

public:
    using NodeT = Node<T,ID_T>;
    using EdgeT = Edge<T,ID_T>;
    using GraphT = Graph<T,ID_T>;

private:
    bool is_directed;
    vector<NodeT*> nodes;

public:
    Graph(bool directed = true); 
    Graph(const Graph& other);
    
    ~Graph();

    /* Member Access Functions*/
    inline size_t size() const { return nodes.size(); }
    inline size_t isEmpty() const { return size() == 0; }
    inline bool isDirected() const { return is_directed;}
    void setDirected(bool directed) { is_directed = directed; }
    
    NodeT * addNode(const T& value, const ID_T& id);    
    void removeNode(NodeT * node);


    EdgeT * addEdge(NodeT * origin, NodeT * target, int weight=1);
    EdgeT * addEdge(const ID_T & origin, const ID_T & target, int weight=1);
    void removeEdge(EdgeT * edge);

    vector<NodeT*> getNodes() const;
    vector<EdgeT*> getEdges() const;
    vector<ID_T>   getIDs() const;
   
    // Functions returning paths followed from a specific node
    vector<vector<EdgeT*>> listPaths(NodeT * origin, NodeT * ignore = nullptr) const;
    vector<vector<EdgeT*>> listPaths(const ID_T & origin) const;

    NodeT * operator[](const ID_T & id);

    /* Quering Functions */
    NodeT * queryById(const ID_T & id) const ;
    EdgeT * queryByEdge(NodeT * origin, NodeT * target) const; 
    EdgeT * queryByEdge(const ID_T & origin, const ID_T & target) const;

    // Functions returtning whether there exists a path between
    // the origin and target node
    bool leadsTo(NodeT * origin, NodeT * target) const;
    bool leadsTo(ID_T origin, ID_T target) const;

    vector<NodeT*> queryByValue(const T& value) const;

    /* Output */ 
    void displayEdges(bool display_values = true, bool display_weight = true, std::ostream & out = std::cout) const;

    void displayPaths(NodeT * node, ostream & out = std::cout) const;
    void displayPaths(const ID_T & id, ostream & out = std::cout ) const;
};

template< typename T, typename ID_T> 
Graph<T,ID_T>::Graph(bool directed) : is_directed(directed) 
{
} 

template< typename T, typename ID_T> 
Graph<T,ID_T>::~Graph() {
    vector<NodeT *> allNodes = getNodes();

    for ( auto node : allNodes ) {
        removeNode(node); // removeNode() deletes node's edges
    }
}

template< typename T, typename ID_T> 
Graph<T,ID_T>::Graph(const Graph& other) {
    is_directed = other.is_directed;
    for ( NodeT * node : other.getNodes() ) {
        addNode(node->getValue(), node->getID());
    }

    for ( EdgeT * edge : other.getEdges() ) {
        addEdge(edge->getOrigin()->getID(), 
                edge->getTarget()->getID(), edge->getWeight());
    }
}

template< typename T, typename ID_T> 
Node<T,ID_T> * Graph<T,ID_T>::addNode(const T& value, const ID_T& id) {
    
    // Throw an exception if the given id
    // was default constructed  
    // or was already present in the graph
    if ( id == ID_T{} || queryById(id) != nullptr )
        throw invalid_id();

    NodeT * node = new NodeT(value, id, this);
    nodes.push_back(node);
    return node;
}

template< typename T, typename ID_T> 
void Graph<T,ID_T>::removeNode(NodeT * node) {
    
    if ( node == nullptr )
        return;

    vector<EdgeT*> edgesToNode = node->edgesToNode();
    vector<EdgeT*> edgesFromNode = node->edgesFromNode();

    for ( auto edge : edgesToNode ) {
        removeEdge(edge);
    }
    
    
    for ( auto edge : edgesFromNode ) {
        removeEdge(edge);
    }

    removeElement(nodes, node);
    delete node;
    
}


template< typename T, typename ID_T> 
Edge<T,ID_T> * Graph<T,ID_T>::addEdge(NodeT * origin, NodeT * target, int weight) {
    
    if ( origin == nullptr || origin->getGraph() != this )
        throw invalid_node();
    
    if ( target == nullptr || target->getGraph() != this )
        throw invalid_node();

    EdgeT * edge = new EdgeT(origin, target, weight);
    origin->links_to.push_back(edge);
    target->linked_from.push_back(edge);

    return edge;
}


template< typename T, typename ID_T> 
Edge<T,ID_T> * Graph<T,ID_T>::addEdge(const ID_T & origin, const ID_T & target, int weight) {

    NodeT * org = queryById(origin);
    NodeT * trg = queryById(target);

    if ( org == nullptr || trg == nullptr )
        throw invalid_id();

    return Graph::addEdge(org, trg, weight);
}


template< typename T, typename ID_T> 
void  Graph<T,ID_T>::removeEdge(EdgeT * edge) {
    if ( edge == nullptr )
        return;

    NodeT * origin = edge->getOrigin();
    NodeT * target = edge->getTarget();

    removeElement(origin->links_to, edge);
    removeElement(target->linked_from, edge);
    delete edge;
}


template< typename T, typename ID_T> 
Node<T,ID_T> * Graph<T,ID_T>::queryById(const ID_T & id) const {
    for ( NodeT * node : nodes )
        if ( node->getID() == id )
            return node;

    return nullptr;
}


template< typename T, typename ID_T> 
Edge<T,ID_T> * Graph<T,ID_T>::queryByEdge(NodeT * origin, NodeT * target) const {
     
    if ( origin == nullptr || origin->getGraph() != this )
        throw invalid_node();
    
    if ( target == nullptr || target->getGraph() != this )
        throw invalid_node();

   for ( EdgeT * edge : origin->edgesFromNode() )
        if ( target == edge->getTarget() ) 
            return edge;

    // If the graph isn't directed search for the edge
    // that is going from the target node to the origin aswell
    if ( !is_directed ) {
        for ( EdgeT * edge : target->edgesFromNode() )
            if ( origin == edge->getTarget() ) 
                return edge;
    }

    return nullptr;
}


template< typename T, typename ID_T> 
Edge<T,ID_T> * Graph<T,ID_T>::queryByEdge(const ID_T & origin, const ID_T & target) const {

    NodeT * org = queryById(origin);
    NodeT * trg = queryById(target);

    if ( org == nullptr || trg == nullptr )
        throw invalid_id();
    
    return queryByEdge(org, trg);
}


template< typename T, typename ID_T> 
vector<Node<T,ID_T> *> Graph<T,ID_T>::queryByValue(const T & value) const {
    vector<NodeT *> result;
    
    for ( NodeT * node : nodes )
        if ( node->getValue() == value )
            result.push_back(node);
    
    return result;
}

template< typename T, typename ID_T> 
vector<Node<T,ID_T> *> Graph<T,ID_T>::getNodes() const { 
    return nodes; 
}

template< typename T, typename ID_T> 
vector<Edge<T,ID_T> *> Graph<T,ID_T>::getEdges() const {
    vector<EdgeT*> edges;
    
    for ( size_t i = 0; i < nodes.size(); ++i) {
        NodeT * orig = nodes[i];
        for ( EdgeT * edge : orig->edgesFromNode() ) {
            edges.push_back(edge);
        }
    }
    return edges;
}

template< typename T, typename ID_T> 
vector<ID_T> Graph<T,ID_T>::getIDs() const {
    vector<ID_T> IDs;
    
    for ( auto node : nodes ) 
        IDs.push_bach(node->getID());
    
    return IDs;
} 

template< typename T, typename ID_T> 
Node<T,ID_T> * Graph<T,ID_T>::operator[](const ID_T & id) {
    return queryById(id);
}


// Return a list of paths (a path is represented as vector<Edge*>)
// that are possible to follow from the "origin" node.
// Example:
// Suppose a graph g is connected like this: 
// ------------------------------
// a -> b-> c-> d
//  \        \-> e
//   \-> f -> h
// ------------------------------
//  Then the list of possible paths from b in g are:
//  1. b -> c
//  2. b -> c -> d
//  3. b -> c -> e
// The ignore parameter allows to specify a node whose path should be ignored 
template< typename T, typename ID_T> 
vector<vector<Edge<T,ID_T> *>> Graph<T,ID_T>::listPaths(NodeT * origin, NodeT *ignore) const { 

    vector<vector<EdgeT *>> paths; 
    vector<EdgeT*> edgesFromOrigin;
    
    if ( origin == nullptr || origin->getGraph() != this )
        throw invalid_node();

    // Fetch the edges going from the origin node depending
    // on the direction of the graph
    if ( isDirected() ) { 
        edgesFromOrigin = origin->edgesFromNode();
    } else {
        edgesFromOrigin = origin->edgesUndirected();
    }

    // If an ignored node was specified remove the edge leading to it
    if ( ignore ) {
        EdgeT * ignore_edge = queryByEdge(origin, ignore);
        removeElement(edgesFromOrigin, ignore_edge);
    }

    // Base case: origin node doesn't contain any edges 
    
    if ( edgesFromOrigin.size() == 0 )
        return paths;

    // Recursive case: call listPaths() for every edge in the origin
    // The edge between the origin node and every target node is 
    // then prepended to paths returned from subsequent listPaths() call

    for ( size_t i = 0; i < edgesFromOrigin.size(); ++i ) {
        EdgeT * edge = edgesFromOrigin[i];
        NodeT * target;
        
        if ( isDirected() || edge->getTarget() != origin ) {
            target = edge->getTarget();
        } else {
            target = edge->getOrigin();
        }

        // Add the edge between the origin and target nodes as a path
        vector<EdgeT*> path;
        path.push_back(edge);
        paths.push_back(path);
        
        // Recursive call to get the paths of the target node
        vector<vector<EdgeT*>> paths_of_target; 
        
        if ( isDirected() ) {
            paths_of_target = listPaths(target);
        } else {
            paths_of_target = listPaths(target,origin);
        }
        
        // Preapend the edge between the origin and target nodes 
        // to every path returned from the listPaths(target) call
        for ( auto & trgt_path : paths_of_target ) {
            vector<EdgeT*> path = trgt_path;
            path.insert(path.begin(), edge);
            paths.push_back(path);
        }
  }
    
    return paths; 
}


template< typename T, typename ID_T> 
vector<vector<Edge<T,ID_T>*>> Graph<T,ID_T>::listPaths(const ID_T & origin) const {
    NodeT * org = queryById(origin);
    
    if ( org == nullptr )
        throw invalid_id();

    return listPaths(org);
}


template< typename T, typename ID_T> 
bool Graph<T,ID_T>::leadsTo(NodeT * origin, NodeT * target) const {
    vector<vector<EdgeT*>> paths = listPaths(origin);
    
    if ( origin == nullptr || origin->getGraph() != this )
        throw invalid_node();
    
    if ( target == nullptr || target->getGraph() != this )
        throw invalid_node();


    for ( auto path : paths ) {
        for ( auto edge : path ) {
            if ( edge->getTarget() ==  target) {
                return true;

            // In case of an undirected graph 
            // the target and the origin can be swapped
            } else if ( !isDirected() && edge->getOrigin() == target) {
                return true;
            }
        }
    }

    return false;
}

template< typename T, typename ID_T> 
bool Graph<T,ID_T>::leadsTo(ID_T origin, ID_T target) const {
    NodeT * orig = queryById(origin);
    NodeT * trgt = queryById(target);
 
    if ( orig == nullptr || trgt == nullptr )
        throw invalid_id();
    
   return leadsTo(orig, trgt);
}      

template< typename T, typename ID_T> 
void Graph<T,ID_T>::displayEdges( bool display_value, bool display_weight,  std::ostream & out) const {
    out << "{";
    for ( size_t i = 0; i < size(); ++i) {
        NodeT * orig = nodes[i];
        for ( EdgeT * edge : orig->edgesFromNode() ) {
            out << "(";
            out << edge->getOrigin()->getID();
            if ( display_value )
                out << ":" << edge->getOrigin()->getValue();
            out << ", " <<  edge->getTarget()->getID();
            if ( display_value )
                out << ":" << edge->getTarget()->getValue();
            if ( display_weight )
                out << " |" << edge->getWeight();
            out << "); ";
        }
    }
    out << "}"; 
}

template< typename T, typename ID_T> 
void Graph<T,ID_T>::displayPaths(NodeT * node, ostream & out) const {
    vector<vector<EdgeT*>> paths = listPaths(node);
    
    if ( node == nullptr )
        throw invalid_node();

    int count = 1;

    if ( isDirected() ) {
        for (auto & path : paths) {
            out << count++ << ". " << path.at(0)->getOrigin()->getID();
            for (auto & edge : path) {
                out << " -> " << edge->getTarget()->getID();
            }
            out << '\n';
        }

    } else {
        for ( auto & path : paths ) {
            out << count++ << ". " << node->getID();
            NodeT * origin = node;
            for ( auto & edge : path ) {
                if ( edge->getTarget() == origin ) {
                    out << " <-> " << edge->getOrigin()->getID();
                    origin = edge->getOrigin();
                } else {
                    out << " <-> " << edge->getTarget()->getID();
                    origin = edge->getTarget();
                }
            }
            out << '\n';
        }
    }
}


template< typename T, typename ID_T> 
void Graph<T,ID_T>::displayPaths(const ID_T & id, ostream & out ) const {
    NodeT * node = queryById(id);

    if ( node == nullptr )
        throw invalid_id();
     

    return displayPaths(node, out);
}

// Helper Function
// Removes an element by value from a generic vector
template <typename ELEM_T>
bool removeElement(vector<ELEM_T> & vec, ELEM_T elem)
{
    typename vector<ELEM_T>::iterator it = vec.begin();
    
    while ( it != vec.end() ) {
        if ( *it == elem ) {
            vec.erase(it);
            return true;
        }
        advance(it,1);
   }
    
    return false;
}

template< typename T, typename ID_T> 
ostream & operator<<(ostream& out, Node<T,ID_T> * node) {
    out << node->getID() << ":" << node->getValue();
    return out;
}


template< typename T, typename ID_T> 
ostream & operator<<(ostream& out, Edge<T,ID_T> *edge){
    out << "(" << edge->getOrigin() << ", "<<edge->getTarget() << " |" << edge->getWeight() << ")";
    return out;
}


template< typename T, typename ID_T> 
ostream & operator<<(ostream & out, const Graph<T,ID_T> & g) {
    out << "(Nodes: {";
    for ( Node<T,ID_T> * node: g.getNodes() ) {
            out  << node->getID() << ": " << node->getValue() << "; ";
    }
    out << "}, Edges: ";
    g.displayEdges(false, true, out);
    out << ")";
    return out;
}

#endif
