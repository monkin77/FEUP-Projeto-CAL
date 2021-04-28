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
    Vertex<T> * orig;
    Vertex<T> * dest;
    double capacity;
    double cost;
    double flow;

    Edge(Vertex<T> *o, Vertex<T> *d, double capacity, double cost=0, double flow=0);

public:
    friend class Graph<T>;
    friend class Vertex<T>;
    double getFlow() const;
};


#endif //FEUP_PROJETO_CAL_EDGE_H
