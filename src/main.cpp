#include <iostream>

#include "graph/Graph.h"
#include "bakery/Client.h"
#include "bakery/Van.h"
#include "utils/Position.h"
#include "utils/GraphBuilder.h"

int main() {
    Graph G;

    defaultGraphBuilder(G);

    G.printGraph();

    return 0;
}
