#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {


    Graph g;

    // Suppose the graph g looks like
    // ------------------------------
    // a -> b-> c-> d
    //  \        \-> e
    //   \-> f -> h
    // ------------------------------
    //  g contains following paths:
    //  1. a -> b -> c -> d
    //  2. a -> b -> c -> e
    //  3. a -> f -> g


    Node * a = g.addNode(1, 'a');
    Node * b = g.addNode(2, 'b');
    Node * c = g.addNode(3, 'c');
    Node * d = g.addNode(4, 'd');
    Node * e = g.addNode(5, 'e');
    /*Node * f = */ g.addNode(6, 'f');
    /*Node * h = */ g.addNode(7, 'h');
    
    // Adding edges between nodes using "Node *"
    g.addEdge(a,b);
    g.addEdge(b,c);
    g.addEdge(c,d);
    g.addEdge(c,e, 15); // giving a weight of 15 to the "c -> e" edge

    // Adding edges between nodes using their "ids"
    g.addEdge('a','f');
    g.addEdge('f','h');

    cout << endl << "Listting Edges:" << endl;
    g.display();
    cout << endl;

    cout << endl << "Listing Paths:" << endl;
    vector<vector<Edge*>> paths = g.listPaths('a');

    for (auto & path : paths) {
        static int count = 1;
        cout << count++ << ". " << path.at(0)->origin->id;
        for (auto & edge : path) {
            cout << " -> " << edge->target->id;
        }
        cout << endl;
    }

    cout << endl;
}
