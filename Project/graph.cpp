#include "graph.h"

#include <iostream>


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


Edge * Graph::addEdge(const ID_T& origin, const ID_T& target, int weight) {
    Node * org = queryById(origin);
    Node * trg = queryById(target);
    return Graph::addEdge(org, trg, weight);
}


Node * Graph::queryById(ID_T id) const {
    for (Node * node : nodes)
        if (node->id == id)
            return node;

    return nullptr;
}


std::vector<Node *> Graph::queryByValue(const T& value) const {
    std::vector<Node *> result;
    
    for ( Node * node : nodes )
        if ( node->value == value )
            result.push_back(node);
    
    return result;
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
