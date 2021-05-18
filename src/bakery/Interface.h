#ifndef FEUP_PROJETO_CAL_INTERFACE_H
#define FEUP_PROJETO_CAL_INTERFACE_H

#include "Bakery.h"

using namespace std;

class Interface {
private:
    Bakery* bakery;
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
