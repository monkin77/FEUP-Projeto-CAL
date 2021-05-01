//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_EDGE_H
#define FEUP_PROJETO_CAL_EDGE_H


using namespace std;

template <class T> class Graph;     // Forward declaration
template <class T> class Vertex;    // Forward declaration

template <class T>
class Edge {
    int id;
    Vertex<T> * orig;  // this might be useful
    Vertex<T> * dest;
    double weight;
public:
    Edge(int id, Vertex<T> *orig, Vertex<T> *dest, double weight);

    int getId() const;
    Vertex<T> *getOrig() const;
    Vertex<T> *getDest() const;
    double getWeight() const;

    friend class Graph<T>;
    friend class Vertex<T>;
};


#endif //FEUP_PROJETO_CAL_EDGE_H
