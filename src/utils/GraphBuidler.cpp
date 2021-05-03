#include "GraphBuilder.h"
#include "Position.h"
#include "Time.h"
#include "../bakery/Client.h"

using namespace std;

void defaultGraphBuilder(Graph &G){
    G.addVertex(Position(1, 1));
    G.addVertex(Position(2, 2));
    G.addVertex(Position(3, 3));
}