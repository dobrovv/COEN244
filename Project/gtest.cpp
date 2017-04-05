#include "graph.h"
#include "directed_graph.h"

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
    cout << "Graph g:"<< endl << g << endl << endl;
    
    // Displaying the first edge in g
    vector<Edge*> edges = g.getEdges();
    cout << "First edge in g:" << endl << edges.at(0) << endl << endl;
    
    // Displaying edges of the graph without values but with weights
    cout << "Edges in g without values displayed:" << endl;
    g.displayEdges(false, true, cout);
    cout << endl << endl;
    
    //
    // Quering the graph
    //
    
    cout << "Listing paths going from a:" << endl;
    vector<vector<Edge*>> paths = g.listPaths('a');

    for (auto & path : paths) {
        int count = 1;
        cout << count++ << ". " << path.at(0)->getOrigin()->getID();
        for (auto & edge : path) {
            cout << " -> " << edge->getTarget()->getID();
        }
        cout << endl;
    }
    cout << endl << endl;

    cout << boolalpha;
    cout << "Does a lead to c?: " << g.leadsTo(a,c) << endl;
    cout << "Does h lead to a?: " << g.leadsTo(g['h'],a) << endl << endl;


    //
    // Removing Nodes and Edges
    //

    // Creating a copy of g
    Graph g_copy(g);
    cout << "Creating a copy of g:" << endl;
    cout << g_copy << endl << endl;

    // Quering the graph to find the a->b edge
    Edge * ab = g_copy.queryByEdge(a,b);
    
    // Removing the edge
    g_copy.removeEdge( ab );

    cout << "Listing the copy of g with a -> b removed:" << endl;
    cout << g_copy << endl << endl;

    g_copy.removeNode(g_copy['f']);
    cout << "Listing the copy of g with f removed:" << endl;
    cout << g_copy << endl << endl;

    //
    // Directed Graph
    //
    
    // Creating a directed graph
    // with nodes a,b,c,d and edges
    // -------------
    // a <-> b <-> c
    //       ^
    //       \-> d <-> e 
    // -------------

    DirectedGraph dg;

    dg.addNode(1,'a');
    dg.addNode(2,'b');
    dg.addNode(3,'c');
    dg.addNode(4,'d');
    dg.addNode(5,'e');

    dg.addEdge(dg['a'],dg['b']);
    dg.addEdge('b','c');
    dg.addEdge('b','d');
    dg.addEdge('d','e');

    cout << "Displaying the Directed Graph dg:" << endl;
    cout << dg << endl << endl;

    cout << "Displaying paths from the b node in dg:" << endl;
    vector<vector<Edge*>> directed_paths = dg.listPaths(dg['b']);

    for (auto & path : directed_paths) {
        int count = 1;
        cout << count++ << ". " << path.at(0)->getOrigin()->getID();
        for (auto & edge : path) {
            cout << " <-> " << edge->getTarget()->getID();
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
