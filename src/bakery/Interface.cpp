#include "Interface.h"
#include <iostream>
#include <string>

using namespace std;

Interface::Interface() {
    bakery = NULL;
    selectedPhase = 1;
}

Interface::~Interface() {
    if (bakery != NULL) delete bakery;
}

void Interface::start() {
    cout << "Welcome to the Bakery's service planner!" << endl;
    cout << "Do you wish to load the information from a file? (Y/N)" << endl;

    char res;
    while (true) {
        cin >> res;
        if (cin.fail() || cin.eof() || (toupper(res) != 'Y' && toupper(res) != 'N')) {
            cout << "That's not a valid answer. Please answer with 'Y' or 'N'" << endl;
            continue;
        }
        break;
    }

    if (toupper(res) == 'N') loadByInput();
    else {
        string file;
        while (true) {
            cout << "Insert the name of the file:" << endl;
            cin >> file;
            if (cin.fail() || cin.eof()) continue;
            break;
        }
        bakery = new Bakery("resources/bakeryInput/" + file);
    }
    servicePlanner();
}

void Interface::servicePlanner() {
    cout << "Select the type of problem you want to solve:" << endl;
    cout << "[1]: Single van visiting all clients without delivery times or capacity" << endl;
    cout << "[2]: Single van visiting all clients with delivery times but no capacity" << endl;
    cout << "[3]: Multiple vans with client allocation, capacity and delivery times" << endl;

    while (true) {
        cin >> selectedPhase;
        if (cin.fail() || cin.eof() || selectedPhase < 1 || selectedPhase > 3) {
            cout << "Invalid choice!" << endl;
            continue;
        }
        break;
    }

    switch (selectedPhase) {
        case 1:
            bakery->solveFirstPhase();
            break;
        case 2:
            bakery->solveSecondPhase();
            break;
        case 3:
            bool useKnapsack, optimize;
            cout << "Do you wish to use knapsack or greedy allocation? (1/2)" << endl;
            cout << "Greedy has generally better but slower results" << endl;

            int choice;
            while (true) {
                cin >> choice;
                if (cin.fail() || cin.eof() || choice < 1 || choice > 2) {
                    cout << "Invalid choice" << endl;
                    continue;
                }
                break;
            }
            useKnapsack = choice == 1;

            cout << "Do you want to optimize the allocation? (Y/N)" << endl;
            cout << "This gives a slightly better but slower result" << endl;

            char res;
            while (true) {
                cin >> res;
                if (cin.fail() || cin.eof() || (toupper(res) != 'Y' && toupper(res) != 'N')) {
                    cout << "Invalid choice" << endl;
                    continue;
                }
                break;
            }
            optimize = toupper(res) == 'Y';

            bakery->solveThirdPhase(useKnapsack, optimize);
            break;
        default:
            break;
    }
}

void Interface::loadByInput() {

}
