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

    int latitude, longitude, numVans, vanCapacity, deliveryTime, maxDelay, maxTimeBefore;
    char token;

    fin >> graphPathName >> token >> latitude >> token >> longitude >> token >> this->radius >> maxDelay >> maxTimeBefore >> numVans;
    this->maxTimeBefore = Time(maxTimeBefore);
    this->maxDelay = Time(maxDelay);

    if( !readGraphFromFile(this->graph, graphPathName) ) {
        cout << "Error reading graph from file" << endl;
        throw runtime_error("File not found (Graph)");
    }

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

        Position clientPosition(latitude, longitude);

        Vertex* clientVertex = this->graph.findVertex(clientPosition);
        if( clientVertex == NULL)
            continue;   // Discard this Client

        clients.push_back(Client(clientId, clientName, clientVertex, Time(hours, minutes), numBread));
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
    van.setClients(clients);
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

void Bakery::filterClients() {
    vector<Client>::iterator it;
    for (it = clients.begin(); it != clients.end(); ++it) {
        Client& c = *it;
        if (graph.findVertex(c.getVertex()->getId()) == NULL) {
            it = clients.erase(it);
            --it;
        }
    }
}

void Bakery::solveFirstPhase() {
    graph.removeUnreachableVertexes(startingVertex, radius);
    filterClients();
    Van& v = vans[0];
    nearestNeighbour(v);
    cout << "Time: " << v.getTotalTime() << endl << "Bread delivered: " << v.getDeliveredBread() << endl << endl;
}

void Bakery::greedyWithDijkstra(Van& van) {
    sort(clients.begin(), clients.end(), [](const Client& c1, const Client& c2) -> bool {
        return c1.getDeliveryTime() < c2.getDeliveryTime();
    });

    Vertex *v1 = startingVertex, *v2;
    Time start(7, 0);
    for (int i = 0; i < clients.size(); ++i) {
        Client& client = clients[i];
        v2 = client.getVertex();
        graph.dijkstraShortestPath(v1, v2);

        Time travelTime(v2->dist);
        Time delay(0);
        Time difference = start + van.getTotalTime() + travelTime - client.getDeliveryTime();
        Time road = travelTime;  // TESTING ONLY

        if ((difference + maxTimeBefore).toMinutes() < 0) {
            // Before time, wait
            travelTime = travelTime - (difference + maxTimeBefore);

        } else if ((difference - maxDelay).toMinutes() > 0) {
            // After time, increase delay
            delay = delay + difference - maxDelay;
        }

        van.makeDelivery(travelTime, delay, client.getBreadQuantity());
        client.setRealTime(start + van.getTotalTime() - van.getDeliveryTime());
        v1 = v2;

        cout << "Visited " << client.getName() << " at: " << client.getRealTime() << endl << "While travelling " << road
        << endl << "Delay: " << delay << endl << "Total: " << van.getTotalTime() << endl << endl;
    }

    this->graph.dijkstraShortestPath(v1, this->startingVertex);
    van.addTime(Time(startingVertex->dist));
    van.setClients(clients);
}

void Bakery::solveSecondPhase() {
    graph.removeUnreachableVertexes(startingVertex, radius);
    filterClients();
    //TODO: Choose the algorithm here. We only have one for now
    Van& v = vans[0];
    greedyWithDijkstra(v);
    cout << "Total Time: " << v.getTotalTime() << endl << "Delay: " << v.getTotalDelay() << endl
    << "Delivered Bread: " << v.getDeliveredBread() << endl;
}
