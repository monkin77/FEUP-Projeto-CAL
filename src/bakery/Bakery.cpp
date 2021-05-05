//
// Created by Domingos Santos on 05/05/2021.
//

#include <fstream>
#include "Bakery.h"

using namespace std;



Bakery::Bakery(const vector<Client> &clients, const vector<Van> &vans, int startVertexId, double radius, int maxDelay,
               int maxTimeBefore) : clients(clients), vans(vans), startVertexId(startVertexId), radius(radius),
                                    maxDelay(maxDelay), maxTimeBefore(maxTimeBefore) {

}

Bakery::Bakery(string filePath) {
    ifstream fin;

    fin.open(filePath);

    if(!fin.is_open())
        throw runtime_error("File not found");

    string line;
    char token;

    string fileName;
   // nome / idCliente / (latitude, longitude) / HH:MM / nº paes
    string name;
    int longitude, latitude, toleranceDelay, toleranceBefore, numVans, deliveryTime, vanCapacity, numClients, clientId, hours, minutes, numBread;
    double radius;

    fin >> fileName >> latitude >> longitude >> radius >> toleranceDelay >> toleranceBefore >> numVans;
    Position P(latitude, longitude);

    // verificar vertice;

    for(int i = 0; i < numVans; i++){
        fin >> vanCapacity >> deliveryTime;
        vans.push_back(Van(vanCapacity, deliveryTime));
    }

    fin >> numClients;

    for(int i = 0; i < numClients; i++){
        fin >> name >> clientId >> latitude >> longitude >> hours >> minutes >> numBread;
        Client C(clientId, name, Position(longitude, latitude), Time(hours, minutes), numBread);
        clients.push_back(C);
    }

}

