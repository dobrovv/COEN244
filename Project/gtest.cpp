#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {

    Graph g;

    // Suppose the required graph g
    // contains nodes a,b,c,d,e,f,h
    // and edges:
    // ------------------------------
    // a -> b-> c-> d
    //  \        \-> e 
    //   \-> f -> h
    // ------------------------------ 
    //  1. a -> b -> c -> d
    //  2. a -> b -> c -> e
    //  3. a -> f -> h

    // 
    // Adding Nodes 
    //
    
    // Graph::addNode() returns a Node * that is used by 
    // the methods of the graph to access the nodes 
    Node * a = g.addNode(1, 'a');
    Node * b = g.addNode(2, 'b');
    auto * c = g.addNode(3, 'c');
    auto * d = g.addNode(4, 'd');
    auto * e = g.addNode(5, 'e');

    // Aleternativly instead of storing the Node * the user 
    // may reffer to the nodes by their IDs
    g.addNode(6, 'f');
    g.addNode(7, 'h');
   

    //
    // Adding Edges
    //

    // Adding edges between the nodes using a saved Node *
    g.addEdge(a,b);
    g.addEdge(b,c);
    g.addEdge(c,d,32); // a weight can be added to each Edge
    g.addEdge(c,e,15); // (the default is 1)

    // Edges can be added using the IDs of their nodes
    // instead of the Node *
    g.addEdge('a','f');
    
    // Graph can also be indexed with IDs to return a Node *
    g.addEdge( g['f'], g['h'] );

   
    //
    // Displaying the graph
    //
    
    // Sending g to the ostream
    cout << "Graph g:"<< endl << g << endl;
    
    // Displaying the first edge in g
    vector<Edge*> edges = g.getEdges();
    cout << "First edge in g:" << endl << edges.at(0) << endl;
    
    // Displaying edges of the graph without values but with weights
    cout << "Edges in g without values:" << endl;
    g.displayEdges(false, true, cout);
    cout << endl;
    
   
    //
    // Removing Nodes and Edges
    //

    // Quering the graph to find the a->b edge
    Edge * ab = g.queryByEdge(a,b);

    // Removing the edge
    g.removeEdge( ab );

    cout << endl << "Listing the graph with a -> b removed:" << endl;
    cout << g << endl;

    //
    // Quering the graph
    //
    
    cout << endl << "Listing Paths:" << endl;
    vector<vector<Edge*>> paths = g.listPaths('b');

    for (auto & path : paths) {
        int count = 1;
        cout << count++ << ". " << path.at(0)->getOrigin()->getID();
        for (auto & edge : path) {
            cout << " -> " << edge->getTarget()->getID();
        }
        cout << endl;
    }
    cout << endl;

    cout << "Does a lead to c?" << g.leadsTo(a,c) << endl;
    cout << "Does a lead to h?" << g.leadsTo(a,g['h']) << endl;

}
