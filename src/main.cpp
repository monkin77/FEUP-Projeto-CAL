#include <iostream>

#include "graph/Graph.h"
#include "bakery/Client.h"
#include "bakery/Van.h"
#include "utils/Position.h"
#include "utils/GraphBuilder.h"

int main() {
    Graph G;

    string path = "maps/GridGraphs/4x4";
    if( !readGraphFromFile(G, path) ) {
        cout << "Error reading graph from file" << endl;
        return 1;
    }

    G.printGraph();

    return 0;
}
