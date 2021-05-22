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
    Bakery(const string &graphFile, const vector<Van> &vans, Position start, double radius, int maxDelay,
           int maxTimeBefore, bool isDirected);

    Bakery(string filePath);
    ~Bakery();
    void solveFirstPhase();
    void solveSecondPhase();
    void solveThirdPhase(bool useKnapsack, bool optimize);
    void filterBakerySCCComponent();

    void addClient(int id, string name, Position pos, Time time, int breadNum);
    void addClient(int id, string name, int vertexID, Time time, int breadNum);

    const vector<Van>& getVans() const;

    Graph getGraph();

    Vertex *getStartingVertex() const;

    double getRadius() const;

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

    // 3rd Phase Algorithms
    void allocateClientsToVans(bool useKnapsack, bool optimize);
    int knapsackAllocation(Van& v, const vector<int>& values);
    int greedyAllocation(Van& v);
};



#endif //FEUP_PROJETO_CAL_BAKERY_H
