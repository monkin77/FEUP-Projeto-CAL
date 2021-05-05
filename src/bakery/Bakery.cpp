//
// Created by Domingos Santos on 05/05/2021.
//

#include <fstream>
#include <iostream>
#include "Bakery.h"
#include "../utils/GraphBuilder.h"

using namespace std;



Bakery::Bakery(const vector<Client> &clients, const vector<Van> &vans, Vertex *startingVertex, double radius,
               int maxDelay, int maxTimeBefore) : clients(clients), vans(vans), startingVertex(startingVertex),
                                                  radius(radius), maxDelay(maxDelay), maxTimeBefore(maxTimeBefore) {}

Bakery::Bakery(string filePath) {
    ifstream fin;

    fin.open(filePath);

    if(!fin.is_open())
        throw runtime_error("File not found (Bakery)");

    string graphPathName, clientName;

    int latitude, longitude, toleranceDelay, toleranceBefore, numVans, vanCapacity, deliveryTime;
    double radius;
    char token;

    fin >> graphPathName >> token >> latitude >> token >> longitude >> token >> radius >> toleranceDelay >> toleranceBefore >> numVans;

    if( !readGraphFromFile(this->graph, graphPathName) ) {
        cout << "Error reading graph from file" << endl;
        throw runtime_error("File not found (Graph)");
    }

    this->graph.printGraph();

    // Confirm valid Bakery Position
    Position bakeryPosition(latitude, longitude);

    Vertex* bakeryVertex = this->graph.findVertex(bakeryPosition);
    if( bakeryVertex == NULL)
        throw runtime_error("Invalid Bakery Position");

   this->startingVertex = bakeryVertex;

    // FETCH VANS

    for(int i = 0; i < numVans; i++){
        fin >> vanCapacity >> deliveryTime;
        vans.push_back( Van( vanCapacity, Time(deliveryTime) ) );
    }

    // FETCH CLIENTS

    int numClients, clientId, hours, minutes, numBread;

    fin >> numClients;

    for(int i = 0; i < numClients; i++){
        fin >> clientName >> clientId >> token >> latitude >> token >> longitude >> token >> hours >> token >> minutes >> numBread;

        // Confirm valid Client Position
        Position clientPosition(latitude, longitude);

        Vertex* clientVertex = this->graph.findVertex(clientPosition);
        if( clientVertex == NULL)
            continue;   // Discard this Client

        Client client(clientId, clientName, clientVertex, Time(hours, minutes), numBread);
        clients.push_back(client);
    }
}
