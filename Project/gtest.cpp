#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    Graph g;
    Node *n1 = g.addNode(33, 1);
    Node *n2 = g.addNode(35, 2);
    g.addEdge(1, 2, 0);
    g.addEdge(n2, n1, 3);

    g.display();

    cout << endl << "Node 2->1 exists: " << (g.queryByEdge(n2, n1) != nullptr) << endl;
}
