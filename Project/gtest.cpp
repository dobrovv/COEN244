#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    Graph<int, char> g;
    
    using NodeT = Graph<int,char>::NodeT;
    using EdgeT = Graph<int,char>::EdgeT;
    
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
    NodeT * a = g.addNode(1, 'a');
    NodeT * b = g.addNode(2, 'b');
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
    vector<EdgeT*> edges = g.getEdges();
    cout << "First edge in g:" << endl << edges.at(0) << endl << endl;
    
    // Displaying edges of the graph with weights and nodes values
    // ex (a:1, b:2 |15), where 1 and 2 are values of nodes 1 and 2and |15 is the weight
    cout << "Edges in g with values displayed:" << endl;
    g.displayEdges(true, true, cout);
    cout << endl << endl;
    
    //
    // Quering the graph
    //
    
    cout << "Listing paths going from a:" << endl;
    //Getting the paths
    vector<vector<EdgeT*>> paths = g.listPaths('a');
    
    //Displaying the paths
    g.displayPaths(a);
    cout << endl;

    // Quering if a particular path exists
    cout << boolalpha;
    cout << "Does a lead to c?: " << g.leadsTo(a,c) << endl;
    cout << "Does h lead to a?: " << g.leadsTo(g['h'],a) << endl << endl;


    //
    // Removing Nodes and Edges
    //

    // Creating a copy of g
    Graph<int,char> g_copy(g);
    cout << "Creating a copy of g:" << endl;
    cout << g_copy << endl << endl;

    // Quering the graph to find the a->b edge
    EdgeT * ab = g_copy.queryByEdge('a','b');
    
    // Removing the edge
    g_copy.removeEdge( ab );

    cout << "Listing the copy of g with a -> b removed:" << endl;
    cout << g_copy << endl << endl;

    g_copy.removeNode(g_copy['f']);
    cout << "Listing the copy of g with f removed:" << endl;
    cout << g_copy << endl << endl;

    //
    // Undirected Graph
    //
    
    // Creating an udirected graph
    // with nodes a,b,c,d and edges
    // -------------
    // a <-> b <-> c
    //       ^
    //       \-> d <-> e 
    // -------------

    Graph<float, string> ug(false);

    ug.addNode(0.5,"a");
    ug.addNode(1,"b");
    ug.addNode(2,"c");
    ug.addNode(3,"d");
    ug.addNode(4,"e");

    ug.addEdge(ug["a"],ug["b"]);
    ug.addEdge("b","c");
    ug.addEdge("b","d");
    ug.addEdge("d","e");

    // Displaying the undirected graph ug "
    cout << "Displaying the Directed Graph ug:" << endl;
    cout << ug << endl << endl;

    cout << "Displaying paths available from the b node in ug:" << endl;
    ug.displayPaths(ug["b"]);
    cout << endl;
    
    cout << boolalpha;
    cout << "Does a lead to e?: " << ug.leadsTo("a","e") << endl;
    cout << "Does e lead to a?: " << ug.leadsTo("e","a") << endl << endl;
    return 0;
}
