#include <iostream>

#include "graph/Graph.h"
#include "bakery/Client.h"
#include "bakery/Van.h"
#include "utils/Position.h"
#include "utils/GraphBuilder.h"
#include "bakery/Bakery.h"

int main() {
    Bakery bakery("bakeryInput/bakery.txt");

    bakery.solveFirstPhase();

    Bakery bakery2("bakeryInput/bakery.txt");
    bakery2.solveSecondPhase();

    return 0;
}
