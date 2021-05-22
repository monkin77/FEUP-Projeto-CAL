#include "Vertex.h"

int Vertex::nextID = 0;

Vertex::Vertex(int id, Position in) {
    this->id = id;
    this->info = in;
    this->client = NULL;
    nextID++;
}

Vertex::Vertex(Position in): info(in) {
    this->id = this->nextID;
    this->nextID++;
    this->client = NULL;
    nextID++;
}

/**
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *dest, int w) {
    adj.push_back(Edge(this, dest, w));
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

Position Vertex::getPosition() const {
    return this->info;
}

int Vertex::getDist() const {
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

Client *Vertex::getClient() const {
    return client;
}

void Vertex::setClient(Client *client) {
    this->client = client;
}
