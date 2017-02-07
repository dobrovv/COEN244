#include "graph.h"

int main() {
    Graph g;
    g.addNode(33, 1);
    g.addNode(35, 2);
    g.addEdge(1, 2, 0);
    g.addEdge(2, 1, 3);

    g.display();
}
