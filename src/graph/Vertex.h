//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_VERTEX_H
#define FEUP_PROJETO_CAL_VERTEX_H

#include <vector>

#include "Edge.h"
#include "MutablePriorityQueue.h"

using namespace std;

template <class T>
class Vertex {
    T info;
    vector<Edge<T> *> outgoing;
    vector<Edge<T> *> incoming;

    bool visited;  // for path finding
    Edge<T> *path; // for path finding
    double dist;   // for path finding
    int queueIndex = 0; // required by MutablePriorityQueue

    Vertex(T in);
    void addEdge(Edge<T> *e);
    bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue

public:
    T getInfo() const;
    vector<Edge<T> *> getIncoming() const;
    vector<Edge<T> *> getOutgoing() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


#endif //FEUP_PROJETO_CAL_VERTEX_H
