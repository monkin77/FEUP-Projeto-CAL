#include <iostream>

#include "bakery/Interface.h"
#include "bakery/InputGenerator.h"

int main() {

    Interface interface;
    interface.start();
    interface.showResultGraphViewer();

    return 0;
}
