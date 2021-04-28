//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_GRAPH_H
#define FEUP_PROJETO_CAL_GRAPH_H

#include <queue>

#include "Vertex.h"

using namespace std;

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    void dijkstraShortestPath(Vertex<T> *s);
    void bellmanFordShortestPath(Vertex<T> *s);
    bool relax(Vertex<T> *v, Vertex<T> *w, Edge<T> *e, double residual, double cost);

    void resetFlows();
    bool findAugmentationPath(Vertex<T> *s, Vertex<T> *t);
    void testAndVisit(queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double flow);

public:
    Vertex<T>* findVertex(const T &inf) const;
    vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in);
    Edge<T> *addEdge(const T &sourc, const T &dest, double capacity, double cost, double flow=0);
    double getFlow(const T &sourc, const T &dest) const ;
    void fordFulkerson(T source, T target);
    double minCostFlow(T source, T target, double flow);
};


#endif //FEUP_PROJETO_CAL_GRAPH_H
