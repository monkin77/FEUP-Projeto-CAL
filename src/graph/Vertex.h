//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_VERTEX_H
#define FEUP_PROJETO_CAL_VERTEX_H

#include <vector>

#include "Edge.h"
#include "../utils/MutablePriorityQueue.h"

using namespace std;

template <class T>
class Vertex {
    int id;
    T info;						// content of the vertex (position)

    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    bool visited = false;		// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);

    int getId() const;
    const vector<Edge<T>> &getAdj() const;
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


#endif //FEUP_PROJETO_CAL_VERTEX_H
