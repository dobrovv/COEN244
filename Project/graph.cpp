#include "graph.h"
#include <iterator>

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
        std::advance(it, 1);
    }
    
    return false;
}

ostream & operator<<(ostream& out, Node * node) {
    out << node->getID() << ":" << node->getValue();
    return out;
}


ostream & operator<<(ostream& out, Edge *edge){
    out << "(" << edge->getOrigin() << ", "<<edge->getTarget() << " |" << edge->getWeight() << ")";
    return out;
}


ostream & operator<<(ostream & out, const Graph & g) {
    out << "(Nodes: {";
    for ( Node * node: g.getNodes() ) {
            out  << node->getID() << ": " << node->getValue() << "; ";
    }
    out << "}, Edges: ";
    g.displayEdges(false, true, out);
    out << ")";
    return out;
}


Graph::Graph(bool directed) : is_directed(directed) {} 

Graph::~Graph() {
    vector<Node *> allNodes = getNodes();

    for ( auto node : allNodes ) {
        removeNode(node); // removeNode() deletes node's edges
    }
}

Graph::Graph(const Graph& other) {
    is_directed = other.is_directed;
    for ( Node * node : other.getNodes() ) {
        addNode(node->getValue(), node->getID());
    }

    for ( Edge * edge : other.getEdges() ) {
        addEdge(edge->getOrigin()->getID(), 
                edge->getTarget()->getID(), edge->getWeight());
    }
}

Node * Graph::addNode(const T& value, const ID_T& id) {
    Node * node = new Node(value, id, this);
    nodes.push_back(node);
    return node;
}

void Graph::removeNode(Node * node) {
    
    if ( node == nullptr )
        return;

    vector<Edge*> edgesToNode = node->edgesToNode();
    vector<Edge*> edgesFromNode = node->edgesFromNode();

    for ( auto edge : edgesToNode ) {
        removeEdge(edge);
    }
    
    for ( auto edge : edgesFromNode ) {
        removeEdge(edge);
    }

    removeElement(nodes, node);
    delete node;
    
}


Edge * Graph::addEdge(Node * origin, Node * target, int weight) {
    Edge * edge = new Edge(origin, target, weight);
    origin->links_to.push_back(edge);
    target->linked_from.push_back(edge);

    return edge;
}


Edge * Graph::addEdge(const ID_T & origin, const ID_T & target, int weight) {
    Node * org = queryById(origin);
    Node * trg = queryById(target);

    return Graph::addEdge(org, trg, weight);
}


void  Graph::removeEdge(Edge * edge) {
    if ( edge == nullptr )
        return;

    Node * origin = edge->getOrigin();
    Node * target = edge->getTarget();

    removeElement(origin->links_to, edge);
    removeElement(target->linked_from, edge);
    delete edge;
}


Node * Graph::queryById(ID_T id) const {
    for ( Node * node : nodes )
        if ( node->id == id )
            return node;

    return nullptr;
}


Edge * Graph::queryByEdge(Node * origin, Node * target) const {
    for ( Edge * edge : origin->edgesFromNode() )
        if ( target == edge->getTarget() ) 
            return edge;

    // If the graph isn't directed search for the edge
    // that is going from the target node to the origin aswell
    if ( !is_directed ) {
        for ( Edge * edge : target->edgesFromNode() )
            if ( origin == edge->getTarget() ) 
                return edge;
    }

    return nullptr;
}


Edge * Graph::queryByEdge(const ID_T & origin, const ID_T & target) const {
    Node * org = queryById(origin);
    Node * trg = queryById(target);

    return queryByEdge(org, trg);
}


vector<Node *> Graph::queryByValue(const T & value) const {
    vector<Node *> result;
    
    for ( Node * node : nodes )
        if ( node->getValue() == value )
            result.push_back(node);
    
    return result;
}

vector<Node*> Graph::getNodes() const { 
    return nodes; 
}

vector<Edge*> Graph::getEdges() const {
    vector<Edge*> edges;
    
    for ( size_t i = 0; i < nodes.size(); ++i) {
        Node * orig = nodes[i];
        for ( Edge * edge : orig->edgesFromNode() ) {
            edges.push_back(edge);
        }
    }
    return edges;
}

Node * Graph::operator[](const ID_T & id) {
    return queryById(id);
}


// Return a list of paths (a path is represented as vector<Edge*>)
// that are possible to follow from the origin node.
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
vector<vector<Edge*>> Graph::listPaths(Node * origin, Node *ignore) const { 
    vector<vector<Edge *>> paths;
    
    vector<Edge*> edgesFromOrigin;
    
    if ( isDirected() ) { 
        edgesFromOrigin = origin->edgesFromNode();
    } else {
        edgesFromOrigin = origin->edgesUndirected();
    }

    // If an ignored node was specified remove the edge leading to it
    if ( ignore ) {
        Edge * ignore_edge = queryByEdge(origin, ignore);
        removeElement(edgesFromOrigin, ignore_edge);
    }

    // Base case: origin node doesn't contain any edges 
    
    if ( edgesFromOrigin.size() == 0 )
        return paths;

    // Recursive case: call listPaths() for every edge in the origin
    // The edge between the origin node and every target node is 
    // then prepended to paths returned from subsequent listPaths() call

    for ( size_t i = 0; i < edgesFromOrigin.size(); ++i ) {
        Edge * edge = edgesFromOrigin[i];
        Node * target;
        
        if ( isDirected() || edge->getTarget() != origin ) {
            target = edge->getTarget();
        } else {
            target = edge->getOrigin();
        }

        // Add the edge between the origin and target nodes as a path
        vector<Edge*> path;
        path.push_back(edge);
        paths.push_back(path);
        
        // Recursive call to get the paths of the target node
        vector<vector<Edge*>> paths_of_target; 
        
        if ( isDirected() ) {
            paths_of_target = listPaths(target);
        } else {
            paths_of_target = listPaths(target,origin);
        }
        
        // Preapend the edge between the origin and target nodes 
        // to every path returned from the listPaths(target) call
        for ( auto & trgt_path : paths_of_target ) {
            vector<Edge*> path = trgt_path;
            path.insert(path.begin(), edge);
            paths.push_back(path);
        }
  }
    
    return paths; 
}


vector<vector<Edge*>> Graph::listPaths(const ID_T & origin) const {
    Node * org = queryById(origin);
    return listPaths(org);
}


bool Graph::leadsTo(Node * origin, Node * target) const {
    vector<vector<Edge*>> paths = listPaths(origin);

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

bool Graph::leadsTo(ID_T origin, ID_T target) const {
    Node * orig = queryById(origin);
    Node * trgt = queryById(target);
    return leadsTo(orig, trgt);
}

void Graph::displayEdges( bool display_value, bool display_weight,  std::ostream & out) const {
    out << "{";
    for ( size_t i = 0; i < size(); ++i) {
        Node * orig = nodes[i];
        for ( Edge * edge : orig->edgesFromNode() ) {
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

void Graph::displayPaths(Node * node, ostream & out) const {
    vector<vector<Edge*>> paths = listPaths(node);

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
            Node * origin = node;
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


void Graph::displayPaths(const ID_T & id, ostream & out ) const {
    Node * node = queryById(id);
    return displayPaths(node, out);
}
