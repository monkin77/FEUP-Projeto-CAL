#include <iostream>

#include "graph/Graph.h"
#include "bakery/Client.h"
#include "bakery/Van.h"
#include "bakery/Bakery.h"

int main() {
    Bakery bakery("resources/bakeryInput/bakery.txt");

    bakery.solveSecondPhase();

    return 0;
}
