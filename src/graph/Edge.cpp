//
// Created by joaog on 4/28/2021.
//

#include "Edge.h"
#include "Graph.h"  // Get the full information about this class (forward declaration)
#include "Vertex.h" // Get the full information about this class (forward declaration)

template<class T>
Edge<T>::Edge(int id, Vertex<T> *orig, Vertex<T> *dest, double weight) {
    this->id = id;
    this->orig = orig;
    this->dest = dest;
    this->weight = weight;
}

template<class T>
int Edge<T>::getId() const {
    return id;
}

template<class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}
