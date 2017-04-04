#include "graph.h"
#include <iterator>

// Helper Function
// removes an element by value from a generic vector
template <typename ELEM_T>
bool Graph::removeElement(vector<ELEM_T> & vec, ELEM_T elem)
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
    out << "{";
    for ( Node * node: g.getNodes() ) {
        for ( Edge * edge: node->edgesFromNode() ) {
            out  << edge << ", ";
        }
    }
    out << "}";
    return out;
}


Graph::Graph() {} 

Graph::~Graph() {
    vector<Node *> allNodes = this->getNodes();

    for ( auto node : allNodes ) {
        removeNode(node); // removeNode() deletes node's edges
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
    for ( Edge * edge : origin->links_to )
        if ( target == edge->target ) 
            return edge;

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
        if ( node->value == value )
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
        for ( Edge * edge : orig->links_to ) {
            edges.push_back(edge);
        }
    }
    return edges;
}

Node * Graph::operator[](const ID_T & id) {
    return queryById(id);
}

// Example:
// Suppose a graph g is  
// ------------------------------
// a -> b-> c-> d
//  \        \-> e
//   \-> f -> h
// ------------------------------
//  Then the node b in g contains following paths:
//  1. b -> c
//  2. b -> c -> d
//  3. b -> c -> e


vector<vector<Edge*>> Graph::listPaths(Node * origin) const { 
    vector<vector<Edge *>> paths;
    
    vector<Edge*> edgesFromOrigin = origin->edgesFromNode();

    // Base case: origin node doesn't contain any edges 
    if ( edgesFromOrigin.size() == 0 )
        return paths;

    // Recursive case: call listPaths() for every edge in the origin
    // The edge between origin node to every target node 
    // is then prepended to each path returned from the listPaths() call

    for ( size_t i = 0; i < edgesFromOrigin.size(); ++i ) {
        Edge * edge_from_origin = edgesFromOrigin[i];
        Node * target = edge_from_origin->getTarget();

        // Add the edge between the origin and target nodes as a path
        vector<Edge*> path;
        path.push_back(edge_from_origin);
        paths.push_back(path);
        
        // Recursive call to get paths of the target node
        vector<vector<Edge*>> target_paths = listPaths(target);
        
        // Preapend the edge between the origin and target nodes 
        // to every path returned from the listPaths(target) call
        for ( auto & trgt_path : target_paths ) {
            vector<Edge*> path = trgt_path;
            path.insert(path.begin(), edge_from_origin);
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
        
        //Ensure that path has at least one edge
        if ( path.size() == 0 )
            return false;

        Edge * last_edge = path[ path.size() -1]; 
        if ( last_edge->getTarget()  == target )
            return true;
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
            out << ( i == size()-1 ? ")" : "), " );
        }
    }
    out << "}"; }
