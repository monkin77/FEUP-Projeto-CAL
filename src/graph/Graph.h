//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_GRAPH_H
#define FEUP_PROJETO_CAL_GRAPH_H

#include <queue>
#include <limits>
#include <unordered_map>

#include "Vertex.h"
#include "../utils/Position.h"
#include "../utils/Time.h"

using namespace std;

constexpr auto INF = std::numeric_limits<double>::max();

class Graph {
    unordered_map<int, Vertex*> vertexMap;
    vector<Vertex*> vertexSet;

    void filterBySCC();
    void filterByRadius(Vertex* start, double radius);

    void DFSVisit(Vertex* v);
public:
    Vertex* findVertex(const Position &inf) const;
    Vertex* findVertex(int idNode) const;

    vector<Vertex *> getVertexSet() const;
    int getNumVertex() const;

    bool addVertex(int id, const Position &in);
    bool addEdge(const Position &sourc, const Position &dest, double weight);
    bool addEdge(int idNodeOrig, int idNodeDest, double weight);

    void removeVertex(int id);

    void printGraph();

    void analyzeConnectivity(Vertex* start);
    void removeUnreachableVertexes(Vertex* start, double radius);

    bool relax(Vertex* v, Edge e);
    void dijkstraShortestPath(Vertex *s);
    void dijkstraShortestPath(Vertex *s, Vertex* d);
};


#endif //FEUP_PROJETO_CAL_GRAPH_H
