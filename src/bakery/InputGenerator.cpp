#include "InputGenerator.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>

#include "../utils/GraphBuilder.h"


Graph InputGenerator::getGraph() {
    return this->G;
}


void InputGenerator::generateBakeryInput() {
    srand(time(NULL));
    vector<string> namesList{"Ana", "Maria", "Joao", "Pedro", "Tiago", "Joana", "Leonor", "Matilde", "Helena", "Rui", "Mario", "Bruno", "Domingos", "Henrique"};
    int numClients, maxDelay, maxTimeBefore, radius, numVans, maxVanCapacity, deliveryDelay, maxClientsBread;
    string path;

    cout << "Insert the map you want: " << endl;
    cin >> path;

    cout << "Insert number of Vans: " << endl;
    cin >> numVans;

    cout << "Insert number of Clients: " << endl;
    cin >> numClients;

    string outputFileName;
    cout << "Insert the name of the output file" << endl;
    cin >> outputFileName;

    ofstream fout;
    fout.open("resources/bakeryInput/" + outputFileName);
    if(!fout.is_open()) {
        cout << "Error opening output file" << endl;
        return;
    }

    string pathPrefix = "resources/maps/";
    path = pathPrefix+path;
    readGraphFromFile(G, path, true);

    radius = 1500;
    maxTimeBefore = 60;
    maxDelay = 60;
    maxVanCapacity = 20;
    deliveryDelay = 1;
    maxClientsBread = 40;

    // Start generating output
    vector<Vertex*> vSet = G.getVertexSet();
    int stringRandomIdx, vertexRandomIdx;
    int vertexID;

    vertexRandomIdx = rand() % G.getNumVertex();
    Vertex *currV = vSet.at(vertexRandomIdx);
    vertexID = currV->getId();
    Position startPos = currV->getPosition();
    G.removeVertex(currV->getId());
    vSet = G.getVertexSet();

    fout << 1 << endl;
    fout << path << endl;
    fout << vertexID << endl;
    fout << radius << " " << maxDelay << " " << maxTimeBefore << endl;
    fout << numVans << endl;

    for(int i = 0; i < numVans; i++) {
        int vanCapacity = 1 + rand() % maxVanCapacity;
        fout << vanCapacity << " " << deliveryDelay << endl;
    }

    fout << numClients << endl;

    for(int i = 0; i < numClients; i++) {
        stringRandomIdx = rand() % namesList.size();
        string name = namesList.at(stringRandomIdx);

        int hour = 7 + (rand() % 13);   // Hour between 7:00 and 19:00
        int minutes = (rand() % 60);    // Minutes between 0 and 59

        int numBread = 1 + (rand() % maxClientsBread);

        while(1) {
            vertexRandomIdx = rand() % G.getNumVertex();
            Vertex *currV = vSet.at(vertexRandomIdx);
            vertexID = currV->getId();
            int dist = currV->getPosition().distance(startPos);
            G.removeVertex(currV->getId());
            vSet = G.getVertexSet();
            if(dist < radius) break;
        }

        fout << name << " " << i << " " << vertexID << " " << hour << ":" << minutes << " " << numBread << endl;
    }

    fout.close();
}

