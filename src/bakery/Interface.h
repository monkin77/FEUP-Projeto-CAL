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
    void printResult(ostream& os);
    void showResultGraphViewer();
    void showSCCGraphViewer();
    void addNodeToGV(Vertex* v);
    void addEdgeToGV(Edge& e, gvEdge::EdgeType edgeType);
    void writeResultInFile();
};


#endif //FEUP_PROJETO_CAL_INTERFACE_H
