//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_GRAPH_H
#define FEUP_PROJETO_CAL_GRAPH_H

#include <queue>
#include <limits>

#include "Vertex.h"

using namespace std;

constexpr auto INF = std::numeric_limits<double>::max();

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    bool relax(Vertex<T>* v, Edge<T> e);
    void dijkstraShortestPath(Vertex<T> *s);
    void dijkstraShortestPath(Vertex<T> *s, Vertex<T>* d);

    void filterBySCC();
    void filterByRadius(Vertex<T>* start, int radius);
public:
    Vertex<T>* findVertex(const T &inf) const;

    vector<Vertex<T> *> getVertexSet() const;
    int getNumVertex() const;

    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double weight);

    void analyzeConnectivity(Vertex<T>* start);
    void removeUnreachableVertexes(Vertex<T>* start, int radius);
};


#endif //FEUP_PROJETO_CAL_GRAPH_H
