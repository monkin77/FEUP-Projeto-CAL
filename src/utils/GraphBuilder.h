#ifndef FEUP_PROJETO_CAL_GRAPHBUILDER_H
#define FEUP_PROJETO_CAL_GRAPHBUILDER_H

#include "../graph/Graph.h"

using namespace std;

void defaultGraphBuilder(Graph &G);

bool readGraphFromFile(Graph &G, string directoryName, bool isStrongComponent);

#endif //FEUP_PROJETO_CAL_GRAPHBUILDER_H
