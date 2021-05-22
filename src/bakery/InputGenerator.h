#ifndef FEUP_PROJETO_CAL_INPUTGENERATOR_H
#define FEUP_PROJETO_CAL_INPUTGENERATOR_H

#include "../graph/Graph.h"

class InputGenerator {
public:
    Graph getGraph();
    void generateBakeryInput();
private:
    Graph G;
};


#endif
