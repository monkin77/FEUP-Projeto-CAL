//
// Created by joaog on 4/28/2021.
//

#include "Graph.h"

using namespace std;

/**
 * Gets the vector of vertices
 */
template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/**
 * Gets the number of vertices in the graph
 */
template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

/**
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/**
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/**
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double weight) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, weight);
    return true;
}

/**
 * Auxiliary function used by Dijkstra
 * Analyzes the path from v to e.dest
 */
template <class T>
bool Graph<T>::relax(Vertex<T> *v, Edge<T> e) {
    Vertex<T>* w = e.dest;
    if (v->dist + e.weight < w->dist) {
        w->dist = v->dist + e.weight;
        w->path = v;
        return true;
    }
    return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(Vertex<T> *s) {
    for (Vertex<T>* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex<T>* v = q.extractMin();
        for (Edge<T> e : v->adj) {
            double oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(Vertex<T> *s, Vertex<T> *d) {
    for (Vertex<T>* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex<T>* v = q.extractMin();

        if (v == d) return;

        for (Edge<T> e : v->adj) {
            double oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}
