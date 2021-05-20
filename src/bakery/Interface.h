#ifndef FEUP_PROJETO_CAL_INTERFACE_H
#define FEUP_PROJETO_CAL_INTERFACE_H

#include "Bakery.h"
#include "InputGenerator.h"
#include "graphviewer.h"

using gvNode = GraphViewer::Node;
using gvEdge = GraphViewer::Edge;

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
    void showSCCsGraphViewer();
    void writeResultInFile();
};


#endif //FEUP_PROJETO_CAL_INTERFACE_H
