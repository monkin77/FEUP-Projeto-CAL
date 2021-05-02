#include "GraphBuilder.h"
#include "Position.h"
#include "Time.h"
#include "../bakery/Client.h"

using namespace std;

void defaultGraphBuilder(Graph &G){
    Position *p1 = new Position(1, 1);
    Position *p2 = new Position(2, 2);
    Position *p3 = new Position(3, 3);

    G.addVertex(*p1);
    G.addVertex(*p2);
    G.addVertex(*p3);
}