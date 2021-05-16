//
// Created by Domingos Santos on 05/05/2021.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include "Bakery.h"
#include "../utils/GraphBuilder.h"

using namespace std;


Bakery::Bakery(const string &graphFile, const vector<Van> &vans, Position start, double radius,
               int maxDelay, int maxTimeBefore) : vans(vans), radius(radius), maxDelay(maxDelay), maxTimeBefore(maxTimeBefore) {

    if (!readGraphFromFile(this->graph, graphFile)) {
        cout << "Error reading graph from file" << endl;
        throw runtime_error("File not found (Graph)");
    }

    startingVertex = graph.findVertex(start);
    if (startingVertex == NULL)
        throw runtime_error("Invalid Bakery Position");
}

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

    if (!readGraphFromFile(this->graph, graphPathName)) {
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

    for (int i = 0; i < numClients; i++) {
        fin >> clientName >> clientId >> token >> latitude >> token >> longitude >> token >> hours >> token >> minutes >> numBread;

        Position clientPosition(latitude, longitude);
        addClient(clientId, clientName, clientPosition, Time(hours, minutes), numBread);
    }
}

void Bakery::addClient(int id, string name, Position pos, Time time, int breadNum) {
    Vertex* v = graph.findVertex(pos);
    if (v == NULL) return; // Discard this Client
    Client* client = new Client(id, name, v, time, breadNum);
    v->setClient(client);
    clients.push_back(client);
}

Bakery::~Bakery() {
    for (Client* client : clients)
        delete client;
}

/**
 * Greedy algorithm that chooses the closest Client at each iteration
 * @return total travel time
 */
void Bakery::nearestNeighbour(Van& van) {
    for(Vertex* v : this->graph.getVertexSet())
        v->visited = false;

    Vertex* v = this->startingVertex;
    int numVisited = -1;    // First increment will be the bakery (not a client)

    while(true) {
        v->visited = true;
        numVisited++;

        if(numVisited == van.getClients().size())
            break;

        vector<Vertex*> clientVertices;
        for (Client* client : van.getClients())
            if(!client->getVertex()->visited)
                clientVertices.push_back(client->getVertex());

        Client *closestClient = this->graph.dijkstraClosestClient(v, clientVertices);
        this->graph.addPathToEdgeList(van.getEdges(), v, closestClient->getVertex());

        v = closestClient->getVertex();

        van.makeDelivery(Time(v->dist), Time(0), closestClient->getBreadQuantity());
    }

    int returningTime = this->graph.bidirectionalDijkstra(v, this->startingVertex);

    van.addTime(Time(returningTime));
    van.setClients(clients);
}

Client *Bakery::getClosestClient() {
    Client* closestClient;
    int minDist = INF;

    for (Client* client : this->clients)
        if (client->getVertex()->dist < minDist && (!client->getVertex()->visited)) {
            minDist = client->getVertex()->dist;
            closestClient = client;
        }

    return closestClient;
}

void Bakery::filterClients() {
    vector<Client *>::iterator it;
    for (it = clients.begin(); it != clients.end(); ++it) {
        Client* c = *it;
        if (graph.findVertex(c->getVertex()->getId()) == NULL) {
            it = clients.erase(it);
            --it;
            delete c;
        }
    }
}

void Bakery::greedyWithDijkstra(Van& van) {
    van.sortClientsByTime();

    Vertex *v1 = startingVertex, *v2;
    Time start(7, 0);
    for (int i = 0; i < van.getClients().size(); ++i) {
        Client* client = van.getClients()[i];
        v2 = client->getVertex();
        graph.dijkstraShortestPath(v1, v2);

        Time travelTime(v2->dist);
        Time delay(0);
        Time difference = start + van.getTotalTime() + travelTime - client->getDeliveryTime();

        if ((difference + maxTimeBefore).toMinutes() < 0) {
            // Before time, wait
            travelTime = travelTime - (difference + maxTimeBefore);

        } else if ((difference - maxDelay).toMinutes() > 0) {
            // After time, increase delay
            delay = delay + difference - maxDelay;
        }

        this->graph.addPathToEdgeList(van.getEdges(), v1, v2);

        client->setRealTime(start + van.getTotalTime() + travelTime);
        van.makeDelivery(travelTime, delay, client->getBreadQuantity());
        v1 = v2;
    }

    van.addTime(Time(graph.bidirectionalDijkstra(v1, startingVertex)));
}

int Bakery::knapsackAllocation(Van &v, const vector<int>& values) {
    vector<Client*> clients;
    for (Client* client : this->clients)
        if (!client->isAllocated()) clients.push_back(client);

    vector<vector<int>> table(clients.size() + 1, vector<int>(v.getTotalBread() + 1));

    for (int i = 0; i <= clients.size(); ++i)
        for (int w = 0; w <= v.getTotalBread(); ++w) {
            if (i == 0 || w == 0)
                table[i][w] = 0;
            else if (clients[i - 1]->getBreadQuantity() <= w)
                table[i][w] = max(values[i - 1] + table[i - 1][w - clients[i - 1]->getBreadQuantity()],
                                  table[i - 1][w]);
            else
                table[i][w] = table[i - 1][w];
        }


    int w = v.getTotalBread(), i = clients.size(), removed = 0;
    while (i > 0) {
        if (table[i][w] - table[i - 1][w - clients[i - 1]->getBreadQuantity()] == values[i - 1]) {
            // Element i should be allocated
            v.addClient(clients[i - 1]);
            removed++;
            w -= clients[i - 1]->getBreadQuantity();
        }
        i--;
    }
    return removed;
}

int Bakery::greedyAllocation(Van &v) {
    int count = 0;
    int capacity = v.getTotalBread();

    while (true) {
        int highestValue = -INF;
        Client *chosen = NULL;

        /*
         * Value = 50000 + 10 * numBreads - 100 * Euclidean(start, pos)
         * Summation(10 * abs(v.clients[i].time - time) - 100 * Euclidean(v.clients[i].pos, pos))
         */
        for (Client *client : clients) {
            if (client->isAllocated()) continue;

            int value = 50000 + 10 * client->getBreadQuantity() - 100 *
                    startingVertex->getPosition().distance(client->getVertex()->getPosition());

            for (Client *client2 : v.getClients())
                value += abs((client2->getRealTime() - client->getRealTime()).toMinutes())
                        - 100 * client2->getVertex()->getPosition().distance(client->getVertex()->getPosition());

            if (value > highestValue && client->getBreadQuantity() <= capacity) {
                highestValue = value;
                chosen = client;
            }
        }
        if (chosen == NULL) break;
        v.addClient(chosen);
        count++;
        capacity -= chosen->getBreadQuantity();
    }
    return count;
}

void Bakery::allocateClientsToVans(bool useKnapsack, bool optimize) {
    sort(vans.begin(), vans.end(), [](const Van& v1, const Van& v2) -> bool {
        return v1.getTotalBread() > v2.getTotalBread();
    });

    int clientsAllocated = 0;

    if (useKnapsack) {
        // Value = breadQuantity / 10 + 1 (the client itself has value)
        vector<int> values;
        for (Van &v : vans) {
            if (clientsAllocated == clients.size()) break;

            for (Client *client : clients)
                values.push_back(client->getBreadQuantity() + 10);

            clientsAllocated += knapsackAllocation(v, values);
            values.clear();
        }
    } else {
        for (Van &v : vans) {
            if (clientsAllocated == clients.size()) break;
            clientsAllocated += greedyAllocation(v);
        }
    }

    if (optimize) {
        /* Since the last used van probably has space left,
         * it will try to take some clients from other vans
         */
        for (int i = vans.size() - 1; i >= 0; --i)
            if (!vans[i].getClients().empty()) {
                for (int j = i - 1; j >= 0; --j) {
                    Client *client = vans[j].removeFarthestClientInRange(vans[i].getReservedBread());
                    if (client != NULL) vans[i].addClient(client);
                }
                break;
            }
    }
}

void Bakery::solveFirstPhase() {
    graph.removeUnreachableVertexes(startingVertex, radius);
    filterClients();
    Van& v = vans[0];
    v.setClients(clients);
    nearestNeighbour(v);
}

void Bakery::solveSecondPhase() {
    graph.removeUnreachableVertexes(startingVertex, radius);
    filterClients();

    Van& v = vans[0];
    v.setClients(clients);
    greedyWithDijkstra(v);
}

void Bakery::solveThirdPhase(bool useKnapsack, bool optimize) {
    graph.removeUnreachableVertexes(startingVertex, radius);
    filterClients();
    allocateClientsToVans(useKnapsack, optimize);
    for (Van& van : vans)
        if (!van.getClients().empty())
            greedyWithDijkstra(van);
}

const vector<Van> &Bakery::getVans() const {
    return vans;
}
