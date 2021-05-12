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

    int latitude, longitude, numVans, vanCapacity, deliveryTime;
    char token;

    fin >> graphPathName >> token >> latitude >> token >> longitude >> token >> this->radius >> this->maxDelay >> this->maxTimeBefore >> numVans;

    if( !readGraphFromFile(this->graph, graphPathName) ) {
        cout << "Error reading graph from file" << endl;
        throw runtime_error("File not found (Graph)");
    }

    // this->graph.printGraph();

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

/**
 * Greedy algorithm that chooses the closest Client at each iteration
 * @return total travel time
 */
void Bakery::nearestNeighbour(Van& van) {
    for(Vertex* v : this->graph.getVertexSet())
        v->visited = false;

    Vertex* v = this->startingVertex;   // Bakery
    int numVisited = -1;    // First increment will be the bakery (not a client)

    while(true) {
        v->visited = true;
        numVisited++;

        if(numVisited == this->clients.size())
            break;

        // We only need to reach the clients' vertices
        vector<Vertex*> clientVertices;
        for (Client& client : this->clients)
            if (!client.getVertex()->visited)
                clientVertices.push_back(client.getVertex());

        this->graph.dijkstraShortestPath(v, clientVertices);

        Client closestClient = getClosestClient();

        v = closestClient.getVertex();
        //TODO: ADD EDGES AND CLIENTS
        van.makeDelivery(Time(v->dist), Time(0), closestClient.getBreadQuantity());
    }

    this->graph.dijkstraShortestPath(v, this->startingVertex);

    // TODO: TIME SHOULDN'T BE DOUBLE
    double returningTime = this->startingVertex->getDist();
    van.addTime(Time(returningTime));
}

Client &Bakery::getClosestClient() {
    Client* closestClient;
    double minDist = INF;

    for (Client& client : this->clients)
        if (client.getVertex()->dist < minDist && (!client.getVertex()->visited)) {
            minDist = client.getVertex()->dist;
            closestClient = &client;
        }

    cout << "Visited " << closestClient->getName()  << endl;
    return *closestClient;
}

void Bakery::solveFirstPhase() {
    graph.removeUnreachableVertexes(startingVertex, radius);
    nearestNeighbour(vans[0]);
    Van& v = vans[0];
    cout << "Time: " << v.getTotalTime() << endl << "Bread delivered: " << v.getDeliveredBread() << endl;
}


