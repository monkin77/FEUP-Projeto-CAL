#ifndef FEUP_PROJETO_CAL_INTERFACE_H
#define FEUP_PROJETO_CAL_INTERFACE_H

#include "Bakery.h"
#include "graphviewer.h"

using NodeGV = GraphViewer::Node;
using EdgeGV = GraphViewer::Edge;

using namespace std;

class Interface {
private:
    Bakery* bakery;
    GraphViewer gv;
    int selectedPhase;
public:
    Interface();
    virtual ~Interface();

    void start();
    void loadByInput();
    void servicePlanner();
    void printResult();
    void showResultGraphViewer();
    void writeResultInFile();
};


#endif //FEUP_PROJETO_CAL_INTERFACE_H
