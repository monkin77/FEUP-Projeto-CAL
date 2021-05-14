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

bool Graph::addEdge(const Position &sourc, const Position &dest, int weight) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, weight);
    v2->addEdge(v1, weight);
    return true;
}

bool Graph::addEdge(int idNodeOrig, int idNodeDest, int weight) {
    Vertex *v1 = this->findVertex(idNodeOrig);
    Vertex *v2 = this->findVertex(idNodeDest);
    if(v1 == NULL || v2 == NULL)
        return false;

    v1->addEdge(v2, weight);
    v2->addEdge(v1, weight);
    return true;
}

void Graph::removeVertex(int id) {
    vertexMap.erase(id);
    for (int i = 0; i < vertexSet.size(); ++i) {
        Vertex* v = vertexSet.at(i);
        if (v->id == id) {
            vertexSet.erase(vertexSet.begin() + i);
            i--;
        }
        for (int j = 0; j < v->adj.size(); ++j) {
            Edge e = v->adj.at(j);
            if (e.dest->id == id) {
                v->adj.erase(v->adj.begin() + j);
                --j;
            }
        }
    }
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
            int oldDist = e.dest->dist;
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
            int oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}

void Graph::DFSVisit(Vertex *v) {
    v->visited = true;
    for (Edge e : v->adj) {
        if (!e.dest->visited) DFSVisit(e.dest);
    }
}

/**
 * Calculate the distance to every Vertex until we have visited all the clients (dests)
 * @param s
 * @param dests
 */
void Graph::dijkstraShortestPath(Vertex *s, vector<Vertex *> dests) {
    for (Vertex* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex* v = q.extractMin();

        // Check if we reached any vertices
        vector<Vertex*>::iterator it;
        if ((it = find(dests.begin(), dests.end(), v)) != dests.end()) {
            dests.erase(it);    // Remove Client from the clients who haven't been delivered
            if (dests.empty()) break;
        }

        for (Edge e : v->adj) {
            int oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }
}

/**
 * Similar to dijkstraShortestPath, but stops when it finds the first client (closest)
 * @param s
 * @param dests
 */
Client* Graph::dijkstraClosestClient(Vertex *s, vector<Vertex *> dests) {
    for (Vertex* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    s->dist = 0;
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        Vertex* v = q.extractMin();

        // Check if we reached any vertices
        vector<Vertex*>::iterator it;
        if ((it = find(dests.begin(), dests.end(), v)) != dests.end()) {
            return v->client;   // Found a Client
        }

        for (Edge e : v->adj) {
            int oldDist = e.dest->dist;
            if (relax(v, e)) {
                if (oldDist == INF) q.insert(e.dest);
                else q.decreaseKey(e.dest);
            }
        }
    }

    return NULL;
}

/**
 * Bidirectional Dijkstra search.
 * @param s
 * @param d
 * @return distance between vertices if successful, -1 otherwise
 */
int Graph::bidirectionalDijkstra(Vertex *s, Vertex *d) {
    for (Vertex* v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
        v->visited = false;
        v->backwardsVisited = false;
    }

    MutablePriorityQueue<Vertex> s_queue, d_queue;

    // Setup source
    s->dist = 0;
    s->visited = true;
    s_queue.insert(s);

    // Setup target
    d->dist = 0;
    d->backwardsVisited = true;
    d_queue.insert(d);

    while(!s_queue.empty() && !d_queue.empty()) {
        Vertex* sV = s_queue.extractMin();

        // Order Edges to maintain the property of visiting the closest Vertex first
        vector<Edge> orderedEdges = sV->adj;
        sort(orderedEdges.begin(), orderedEdges.end(), [&](const Edge& e1,const Edge& e2){
            return e1.weight < e2.weight;
        });
        for(Edge& e : orderedEdges) {
            Vertex* destV = e.dest;
            if( destV->backwardsVisited == true){   // If it has already been visited in the other direction
                int totalDistance = this->joinBidirectionalDistances(destV, sV, e.weight);
                return totalDistance;
            }

            int oldDist = e.dest->dist;
            if(relax(sV, e)) {
                destV->visited = true;
                if(oldDist == INF) s_queue.insert(e.dest);
                else s_queue.decreaseKey(e.dest);
            }
        }

        Vertex* dV = d_queue.extractMin();
        // Order Edges to mantain the property of visiting the closest Vertex first
        orderedEdges = dV->adj;
        sort(orderedEdges.begin(), orderedEdges.end(), [&](const Edge& e1,const Edge& e2){
            return e1.weight < e2.weight;
        });

        for(Edge& e : orderedEdges) {
            Vertex* destV = e.dest;
            if( destV->visited == true){   // If it has already been visited in the other direction
                int totalDistance = this->joinBidirectionalDistances(destV, dV, e.weight);
                return totalDistance;
            }

            int oldDist = e.dest->dist;
            if(relax(dV, e)) {
                destV->backwardsVisited = true;
                if(oldDist == INF) d_queue.insert(e.dest);
                else d_queue.decreaseKey(e.dest);
            }
        }
    }
    return -1;
}

int Graph::joinBidirectionalDistances(Vertex *intersectionVertex, Vertex *oppDirectionVertex, int oppDirectionWeight) {
    return intersectionVertex->dist + oppDirectionVertex->dist + oppDirectionWeight;
}

/**
 * THIS IS JUST FOR AN UNDIRECTED GRAPH
 */
void Graph::analyzeConnectivity(Vertex *start) {
    for (Vertex* v : vertexSet)
        v->visited = false;
    DFSVisit(start);
}


void Graph::removeUnreachableVertexes(Vertex* start, double radius) {
    filterByRadius(start, radius);
    analyzeConnectivity(start);
    filterBySCC();
}

/**
 * Removes vertexes not in the start's strongly connected component
 * Should be called after analyzeConnectivity()
 */

void Graph::filterBySCC() {
    for (int i = 0; i < vertexSet.size(); ++i) {
        Vertex* v = vertexSet.at(i);
        if (!v->visited) {
            removeVertex(v->id);
            --i;
        }
    }
}

/**
 * Removes vertexes not in the range of a given radius, when comparing to start
 */

void Graph::filterByRadius(Vertex* start, double radius) {
    for (int i = 0; i < vertexSet.size(); ++i) {
        Vertex* v = vertexSet.at(i);
        if (start->getPosition().distance(v->getPosition()) > radius) {
            removeVertex(v->id);
            --i;
        }
    }
}

void Graph::printGraph() {
    for(Vertex *v : this->vertexSet){
        cout << "Vertex id: " << v->id << " " << v->info << endl;

        for(Edge e : v->adj) {
            cout << "   " << e << endl;
        }
    }
}
