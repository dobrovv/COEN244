#include "directed_graph.h"

DirectedGraph::DirectedGraph() {

}

DirectedGraph::~DirectedGraph() {

}

Edge * DirectedGraph::addEdge(Node * origin, Node * target, int weight){
    Edge * primary = Graph::addEdge(origin, target, weight);
    Graph::addEdge(target, origin, weight);
    return primary;
}

Edge * DirectedGraph::addEdge(const ID_T & origin, const ID_T & target, int weight)
{
    Edge * primary = Graph::addEdge(origin, target, weight);
    Graph::addEdge(target, origin, weight);
    return primary;

}

void DirectedGraph::removeEdge(Edge * edge) {
    Graph::removeEdge(edge);
    Graph::removeEdge(queryByEdge(edge->getTarget(), edge->getOrigin()));
}
    

// Functions returning paths followed from a specific node
// The ignore parameter allows to specify a node whose path should be ignored 
vector<vector<Edge*>> DirectedGraph::listPaths(Node * origin, Node * ignore) const {
    vector<vector<Edge*>> paths;

    // Get the edges going from the origin
    vector<Edge*> edgesFromOrigin = origin->edgesFromNode();
   
    // If an ignored node was specified remove the edge leading to it
    if ( ignore ) {
        Edge * ignore_edge = queryByEdge(origin, ignore);
        removeElement(edgesFromOrigin, ignore_edge);
    }


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
        vector<vector<Edge*>> target_paths = listPaths(target, origin);
        
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

vector<vector<Edge*>> DirectedGraph::listPaths(const ID_T & origin) const {
    Node * org = queryById(origin);
    return listPaths(org);
}
