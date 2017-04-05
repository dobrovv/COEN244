#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "graph.h"

class DirectedGraph : public Graph {
public:
    DirectedGraph();
    DirectedGraph(const DirectedGraph& other); 
    ~DirectedGraph();
   
    
    Edge * addEdge(Node * origin, Node * target, int weight=1);
    Edge * addEdge(const ID_T & origin, const ID_T & target, int weight=1);
    void removeEdge(Edge * edge);
    

    // Functions returning paths followed from a specific node
    // The ignore parameter allows to specify a node whose path should be ignored 
    vector<vector<Edge*>> listPaths(Node * origin, Node * ignore=nullptr) const;
    vector<vector<Edge*>> listPaths(const ID_T & origin) const;
};


#endif //!DIRECTED_GRAPH_H
