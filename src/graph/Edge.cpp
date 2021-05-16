#include "Edge.h"
#include "Graph.h"

int Edge::nextId = 0;

Edge::Edge() {
    this->id = -1;
    this->orig = NULL;
    this->dest = NULL;
    this->weight = INF;
}

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

ostream &operator<<(ostream &os, const Edge &edge) {
    os << "id: " << edge.id << " orig: " << edge.orig->getId() << " dest: " << edge.dest->getId() << " weight: " << edge.weight;
    return os;
}
