//
// Created by joaog on 4/28/2021.
//

#include "Edge.h"
#include "Graph.h"  // Get the full information about this class (forward declaration)
#include "Vertex.h" // Get the full information about this class (forward declaration)

int Edge::nextId = 0;

Edge::Edge(Vertex *orig, Vertex *dest, double weight) {
    this->id = this->nextId;
    this->nextId++;

    this->orig = orig;
    this->dest = dest;
    this->weight = weight;
}


int Edge::getId() const {
    return id;
}


Vertex *Edge::getOrig() const {
    return orig;
}


Vertex *Edge::getDest() const {
    return dest;
}


double Edge::getWeight() const {
    return weight;
}
