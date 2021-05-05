//
// Created by joaog on 4/28/2021.
//

#include "Vertex.h"

int Vertex::nextID = 0;

Vertex::Vertex(int id, Position in) {
    this->id = id;
    this->info = in;
}

Vertex::Vertex(Position in): info(in) {
    this->id = this->nextID;
    this->nextID++;
}

/**
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *dest, double w) {
    adj.push_back(Edge(this, dest, w));
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

Position Vertex::getInfo() const {
    return this->info;
}

double Vertex::getDist() const {
    return this->dist;
}

Vertex *Vertex::getPath() const {
    return this->path;
}

int Vertex::getId() const {
    return id;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}
