//
// Created by Domingos Santos on 05/05/2021.
//

#ifndef FEUP_PROJETO_CAL_BAKERY_H
#define FEUP_PROJETO_CAL_BAKERY_H

#include "Client.h"
#include "Van.h"
#include "../graph/Graph.h"


class Bakery {
public:
    Bakery(const vector<Client *> &clients, const vector<Van> &vans, Vertex* startingVertex, double radius, int maxDelay,
           int maxTimeBefore);

    Bakery(string filePath);
    ~Bakery();
    void solveFirstPhase();
    void solveSecondPhase();

private:
    vector<Client *> clients;
    vector<Van> vans;
    Vertex* startingVertex;
    double radius;
    Time maxDelay;
    Time maxTimeBefore;
    Graph graph;

    // Common methods
    Client* getClosestClient();
    void filterClients();

    // 1st Phase Algorithms
    void nearestNeighbour(Van& van);

    // 2nd Phase Algorithms
    void greedyWithDijkstra(Van& van);
};



#endif //FEUP_PROJETO_CAL_BAKERY_H
