#include <iostream>

#include "bakery/Interface.h"
#include "graphviewer.h"

using gvNode = GraphViewer::Node;
using gvEdge = GraphViewer::Edge;

int main() {
    Interface interface;
    interface.start();
    interface.showResultGraphViewer();

    return 0;
}
