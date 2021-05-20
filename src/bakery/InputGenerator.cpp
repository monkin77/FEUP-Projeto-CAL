//
// Created by Domingos Santos on 20/05/2021.
//
#include "InputGenerator.h"

#include <iostream>
#include <fstream>
#include "math.h"
#include <vector>
#include "graphviewer.h"
#include "../bakery/Client.h"
#include "../utils/GraphBuilder.h"
#include "../graph/Graph.h"


Graph InputGenerator::getGraph() {
    return this->G;
}


void InputGenerator::generateBakeryInput() {
    vector<string> aux{"Ana", "Maria", "João", "Pedro", "Tiago", "Joana", "Leonor", "Matilde", "Helena", "Rui", "Mário", "Bruno", "Domingos", "Henrique"};
    cout << "Insert the map you want: ";
    int numClients, maxDelay, maxTimeBefore, radius, numVans, vanCapacity, deliveryTime;

    string path;
    cin >> path;

    ofstream fin;
    fin.open(path);

    cout << "Insert number of Vans: ";
    cin >> numVans;
    cout << endl;

    cout << "Insert number of Clients: ";
    cin >> numClients;
    cout << endl;

    cout << "Insert radius: ";
    cin >> radius;
    cout << endl;

    cout << "Insert maxTimeBefore: ";
    cin >> maxTimeBefore;
    cout << endl;

    cout << "Insert maximum delay: ";
    cin >> maxDelay;
    cout << endl;

    cout << "Insert van's capacity: ";
    cin >> vanCapacity;
    cout << endl;

    cout << "Insert delivery time: ";
    cin >> deliveryTime;
    cout << endl;

    vector<Client> clients;

    string pathPrefix = "resources/maps/";

    path = pathPrefix+path;

    readGraphFromFile(G, path);

    vector<Vertex*> longlat = G.getVertexSet();
    int index = rand() % G.getNumVertex();
    Vertex *V = longlat.at(index);
    G.removeVertex(V->getId());

    fin << 1;
    fin << path;
    fin << V->getPosition().getLatitude() << V->getPosition().getLongitude();
    fin << radius << maxDelay << maxTimeBefore;
    fin << numVans;
    fin << vanCapacity << deliveryTime;
    fin << numClients;


    for(int i = 0; i < numClients; i++){
        const string name = aux.at(rand() % aux.size());
        int hour = 7 + (rand() % 13);
        int minutes = (rand() & 61);
        Time *t = new Time(hour, minutes);
        int numBread = 1 + (rand() % 10);
        int indexGraph = rand() % G.getNumVertex();
        vector<Vertex*> vSet = G.getVertexSet();
        Vertex *V = vSet.at(indexGraph);
        G.removeVertex(V->getId());
        fin << name << i << "(" << V->getPosition().getLatitude() << "," << V->getPosition().getLongitude() << ")" << hour << ":" << minutes << numBread;
    }
}

