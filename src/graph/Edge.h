//
// Created by joaog on 4/28/2021.
//

#ifndef FEUP_PROJETO_CAL_EDGE_H
#define FEUP_PROJETO_CAL_EDGE_H


#include <ostream>

using namespace std;

class Graph;     // Forward declaration
class Vertex;    // Forward declaration


class Edge {
    int id;
    Vertex * orig;  // this might be useful
    Vertex * dest;
    double weight;
public:
    static int nextId;
    Edge();
    Edge(Vertex *orig, Vertex *dest, double weight);    // increments the nextID variable

    int getId() const;
    Vertex *getOrig() const;
    Vertex *getDest() const;
    double getWeight() const;

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge);

    friend class Graph;
    friend class Vertex;
};


#endif //FEUP_PROJETO_CAL_EDGE_H
