#include "graph.h"

Graph::Graph( const vector<Node*> & nodes, const vector<Edge> & edges) {
    
    this->nodes.reserve(nodes.size());
    
    for ( auto node : nodes ) {
        this->nodes.push_back(node);
    }

    for ( auto edge : edges ) {
        Node * source = edge.first;
        Node * target = edge.second;

        source->links_to.push_back(target);
        target->linked_from.push_back(source);
    }
}
                                           
