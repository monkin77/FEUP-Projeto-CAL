//
// Created by joaog on 4/28/2021.
//

#include <iostream>
#include "Graph.h"
#include "../utils/Position.h"

using namespace std;

/**
 * Gets the vector of vertices
 */

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * Gets the number of vertices in the graph
 */

int Graph::getNumVertex() const {
    return vertexSet.size();
}

/**
 * Auxiliary function to find a vertex with a given content.
 */

Vertex* Graph::findVertex(const Position &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

Vertex* Graph::findVertex(int idNode) const {
    auto nodeTuple = this->vertexMap.find(idNode);
    if(nodeTuple == this->vertexMap.end())
        return NULL;
    return nodeTuple->second;
}

/**
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(int id, const Position &in) {
    if ( findVertex(in) != NULL)
        return false;
    Vertex* newVertex = new Vertex(id, in);

    vertexSet.push_back(newVertex); // Need to check if this vertexSet is needed
    this->vertexMap.insert(pair<int, Vertex*>(id, newVertex));

    return true;
}

/**
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Position &sourc, const Position &dest, double weight) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addEdge(int idNodeOrig, int idNodeDest, double weight) {
    Vertex *v1 = this->findVertex(idNodeOrig);
    Vertex *v2 = this->findVertex(idNodeDest);
    if(v1 == NULL || v2 == NULL)
        return false;

    v1->addEdge(v2, weight);
    return true;
}

/**
 * Auxiliary function used by Dijkstra
 * Analyzes the path from v to e.dest
 */

bool Graph::relax(Vertex *v, Edge e) {
    Vertex* w = e.dest;
    if (v->dist + e.weight < w->dist) {
        w->dist = v->dist + e.weight;
        w->path = v;
        return true;
    }
    return false;
}


void Graph::dijkstraShortestPath(Vertex *s) {
    for (Vertex* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex* v = q.extractMin();
        for (Edge e : v->adj) {
            double oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}


void Graph::dijkstraShortestPath(Vertex *s, Vertex *d) {
    for (Vertex* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex* v = q.extractMin();

        if (v == d) return;

        for (Edge e : v->adj) {
            double oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}


void Graph::analyzeConnectivity(Vertex *start) {
    /* TODO
     * THIS DEPENDS IF THE GRAPH IS DIRECTED OR NOT
     * IT'S MUCH EASIER TO HAVE IT UNDIRECTED. ASK THE TEACHER
     */
}


void Graph::removeUnreachableVertexes(Vertex* start, int radius) {
    filterByRadius(start, radius);
    analyzeConnectivity(start);
    filterBySCC();
}

/**
 * Removes vertexes not in the start's strongly connected component
 * Should be called after analyzeConnectivity()
 */

void Graph::filterBySCC() {
    // TODO
}

/**
 * Removes vertexes not in the range of a given radius, when comparing to start
 */

void Graph::filterByRadius(Vertex* start, int radius) {
    // TODO
    // Maybe, we should only erase clients not in the radius instead of all the vertexes?
}

void Graph::printGraph() {
    for(Vertex *v : this->vertexSet){
        cout << "Vertex id: " << v->id << " " << v->info << endl;

        for(Edge e : v->adj) {
            cout << "   " << e << endl;
        }
    }
}
