//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_VERTEX_H
#define FEUP_PROJETO_CAL_VERTEX_H

#include <vector>

#include "Edge.h"
#include "../utils/MutablePriorityQueue.h"
#include "../utils/Position.h"

using namespace std;


class Vertex {
    int id;
    Position info;						// content of the vertex (position)

    std::vector<Edge > adj;		// outgoing edges

    double dist = 0;
    Vertex *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    bool visited = false;		// auxiliary field

    void addEdge(Vertex *dest, double w);

public:
    static int nextID;
    Vertex(Position in);
    Vertex(int id, Position in);
    Vertex() {this->info = Position();};

    int getId() const;
    const vector<Edge> &getAdj() const;
    Position getPosition() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex & vertex) const; // required by MutablePriorityQueue
    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
    friend class Bakery;
};


#endif //FEUP_PROJETO_CAL_VERTEX_H
