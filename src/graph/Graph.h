//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_GRAPH_H
#define FEUP_PROJETO_CAL_GRAPH_H

#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

#include "Vertex.h"
#include "../utils/Position.h"
#include "../utils/Time.h"

using namespace std;

constexpr auto INF = std::numeric_limits<int>::max();

class Graph {
    unordered_map<int, Vertex*> vertexMap;
    vector<Vertex*> vertexSet;

    void filterBySCC();
    void filterByRadius(Vertex* start, double radius);
    void analyzeConnectivity(Vertex* start);

    void DFSVisit(Vertex* v);
    bool relax(Vertex* v, Edge e);
public:
    Vertex* findVertex(const Position &inf) const;
    Vertex* findVertex(int idNode) const;

    vector<Vertex *> getVertexSet() const;
    int getNumVertex() const;

    bool addVertex(int id, const Position &in);
    bool addEdge(const Position &sourc, const Position &dest, int weight);
    bool addEdge(int idNodeOrig, int idNodeDest, int weight);

    void removeVertex(int id);

    void printGraph();

    void removeUnreachableVertexes(Vertex* start, double radius);

    void dijkstraShortestPath(Vertex *s);
    void dijkstraShortestPath(Vertex *s, Vertex* d);
    void dijkstraShortestPath(Vertex *s, vector<Vertex*> dests);
    Client* dijkstraClosestClient(Vertex *s, vector<Vertex*> dests);

    int bidirectionalDijkstra(Vertex *s, Vertex *d);
    int joinBidirectionalDistances(Vertex* intersectionVertex, Vertex* oppDirectionVertex, int oppDirectionWeight);
};


#endif //FEUP_PROJETO_CAL_GRAPH_H
