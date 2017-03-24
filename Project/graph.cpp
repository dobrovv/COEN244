#include "graph.h"


Graph::Graph() {} 


Node * Graph::addNode(const T& value, const ID_T& id) {
    Node * node = new Node;

    node->value = value;
    node->id    = id;
    node->graph = this;

    nodes.push_back(node);
    return node;
}


Edge * Graph::addEdge(Node * origin, Node * target, int weight) {
    Edge * edge = new Edge;

    edge->origin = origin;
    edge->target = target;
    edge->weight = weight;

    origin->links_to.push_back(edge);
    target->linked_from.push_back(edge);

    return edge;
}


Edge * Graph::addEdge(const ID_T & origin, const ID_T & target, int weight) {
    Node * org = queryById(origin);
    Node * trg = queryById(target);

    return Graph::addEdge(org, trg, weight);
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


// Example:
// Suppose a graphs looks like this 
// ------------------------------
// a -> b-> c-> d
// \         \-> e
//  \-> f -> g
// ------------------------------
//  Then the graph contains following paths:
//  1. a -> b -> c -> d
//  2. a -> b -> c -> e
//  3. a -> f -> g


vector<vector<Edge*>> Graph::listPaths(Node * origin) const { 
    vector<vector<Edge *>> paths;
    
    // Basis case: origin node doesn't link to any other nodes 
    
    if ( origin->links_to.size() == 0 )
        return paths;

    // Recursive case: call listPaths() for every node linked from the origin
    // The edge linking the orign node to each target node 
    // is prepended to the paths returned from the listPaths() call

    for ( size_t i = 0; i < origin->links_to.size(); ++i ) {
        Edge * edge_to_target = origin->links_to[i];
        Node * target = edge_to_target->target;

        // Recursive call
        vector<vector<Edge*>> target_paths = listPaths(target);
        
        if ( target_paths.size() == 0) { 
            // if target doesn't link to any other nodes ( is a terminal node )
            // then the edge between the origin and target node is the whole path
            
            vector<Edge*> path;
            path.push_back(edge_to_target);
            paths.push_back(path);

        } else {
            // else preapend the edge between the origin and target nodes to every path
            // returned from the listPaths(target) call

            for ( auto & trgt_path : target_paths ) {
                vector<Edge*> path = trgt_path;
                path.insert(path.begin(), edge_to_target);
                paths.push_back(path);
            }
        }
    }
    
    return paths; 
}


vector<vector<Edge*>> Graph::listPaths(const ID_T & origin) const {
    Node * org = queryById(origin);
    return listPaths(org);
}

void Graph::display( bool display_value, bool display_weight,  std::ostream & out) const {
    out << "{";
    for ( size_t i = 0; i < nodes.size(); ++i) {
        Node * orig = nodes[i];
        for ( Edge * edge : orig->links_to ) {
            out << "(";
            out << edge->origin->id;
            if ( display_value )
                out << ":" << edge->origin->value;
            out << ", " <<  edge->target->id;
            if ( display_value )
                out << ":" << edge->target->value;
            if ( display_weight )
                out << " |" << edge->weight;
            out << ( i == size()-1 ? ")" : "), " );
        }
    }
    out << "}";
}
