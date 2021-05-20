#include <iostream>

#include "bakery/Interface.h"
#include "bakery/InputGenerator.h"

int main() {

    Interface interface;
    interface.start();
    interface.showResultGraphViewer();

    /*
    InputGenerator gen;
    gen.generateBakeryInput();
    */
    return 0;
}
