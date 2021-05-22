#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>

#include "bakery/Interface.h"
using namespace std;

vector<pair<string, int>> files = {
                                    make_pair("nn1.txt", 1),
                                    make_pair("nn2.txt", 10),
                                    make_pair("nn3.txt", 50),
                                    make_pair("nn4.txt", 100),
                                    make_pair("nn5.txt", 500),
                                    make_pair("nn6.txt", 1000),
                                    make_pair("nn7.txt", 2000),
                                    make_pair("nn10.txt", 3000),
                                    make_pair("nn11.txt", 4000),
                                    make_pair("nn8.txt", 5000),
                                    make_pair("nn12.txt", 6000),
                                    make_pair("nn9.txt", 7000)
                                };

int main() {
    InputGenerator inputGenerator;
    //inputGenerator.generateBakeryInput();

    ofstream fout;
    fout.open("nn_results.txt");

    for (auto test : files) {
        auto start = std::chrono::high_resolution_clock::now();

        Bakery bakery("resources/bakeryInput/" + test.first);
        bakery.solveFirstPhase();

        auto finish = std::chrono::high_resolution_clock::now();
        auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

        fout << test.second << "," << mili << endl;
    }


    return 0;
}
