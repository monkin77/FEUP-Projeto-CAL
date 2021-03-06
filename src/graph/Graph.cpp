#include <iostream>
#include "Graph.h"

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
    if(!isDirected) v2->addEdge(v1, weight);
    return true;
}

bool Graph::addEdge(int idNodeOrig, int idNodeDest, int weight) {
    Vertex *v1 = this->findVertex(idNodeOrig);
    Vertex *v2 = this->findVertex(idNodeDest);
    if(v1 == NULL || v2 == NULL)
        return false;

    v1->addEdge(v2, weight);
    if(!isDirected) v2->addEdge(v1, weight);
    return true;
}

void Graph::removeVertex(int id) {
    Vertex* removableVertex = vertexMap.at(id);
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
    if (removableVertex->client != NULL)
        removableVertex->client->setVertex(NULL);
    delete removableVertex;
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
        w->pathEdge = e;
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
 * Finds the Edge in the opposite direction of e (Only works on undirectional graphs)
 * @param e
 * @return Edge if exists, NULL otherwise
 */
const Edge* Graph::findSymmetricEdge(Edge &e) {
    Vertex* src = e.getOrig();
    Vertex* dest = e.getDest();

    for(const Edge& oppositeEdge : dest->getAdj()) {
        if(oppositeEdge.getDest() == src)
            return &oppositeEdge;
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

    for(Edge& e : s->adj) {
        if(e.dest == d) {
            d->dist = INF;
            if(relax(s, e)) e.dest->visited = true;
            return e.dest->dist;
        }
    }

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
                d->dist = totalDistance;
                // Set the path for the intersection vertex to be in the right direction
                Vertex* oppositeStart = destV->path;
                Edge oppositeEdge = destV->pathEdge;
                destV->path = sV;
                destV->pathEdge = e;
                this->invertOppositeEdges(oppositeStart, oppositeEdge, destV, d);
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
            if( destV->visited == true) {   // If it has already been visited in the other direction
                int totalDistance = this->joinBidirectionalDistances(destV, dV, e.weight);
                d->dist = totalDistance;
                this->invertOppositeEdges(dV, e, destV, d);
                return totalDistance;
            }

            int oldDist = e.dest->dist;
            if(relax(dV, e)) {
                destV->backwardsVisited = true;
                if(oldDist == INF)
                    d_queue.insert(e.dest);
                else
                    d_queue.decreaseKey(e.dest);
            }
        }
    }
    return -1;
}

int Graph::joinBidirectionalDistances(Vertex *intersectionVertex, Vertex *oppDirectionVertex, int oppDirectionWeight) {
    return intersectionVertex->dist + oppDirectionVertex->dist + oppDirectionWeight;
}

/**
 * Auxiliary function that fixes the path / pathEdge of vertices that travelled in the oppposite direction
 * @param oppositeStart
 * @param edge
 * @param intersectionVertex
 * @param lastVertex
 */
void Graph::invertOppositeEdges(Vertex *oppositeStart, Edge &edge, Vertex *intersectionVertex, Vertex* lastVertex) {
    Vertex* currVertex = oppositeStart;
    Vertex* nextVertex = currVertex->path;
    Vertex* vertexBefore = intersectionVertex;

    Edge savedPathEdge;

    currVertex->path = vertexBefore;
    const Edge& symmetricEdge = *this->findSymmetricEdge(edge);
    savedPathEdge = currVertex->pathEdge;
    currVertex->pathEdge = symmetricEdge;

    while(true) {
        vertexBefore = currVertex;
        currVertex = nextVertex;
        if(currVertex == nullptr) break;
        nextVertex = currVertex->path;

        currVertex->path = vertexBefore;
        const Edge& symmetricEdge = *this->findSymmetricEdge(savedPathEdge);
        savedPathEdge = currVertex->pathEdge;
        currVertex->pathEdge = symmetricEdge;

        if(currVertex == lastVertex) break;
    }
}

/**
 * THIS IS JUST FOR AN UNDIRECTED GRAPH
 */
void Graph::analyzeConnectivity(Vertex *start) {
    for (Vertex* v : vertexSet)
        v->visited = false;
    if (this->isDirected) this->calculateSccTarjan(start);
    else DFSVisit(start);
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

void Graph::addPathToEdgeList(vector<Edge> &edges, Vertex* source, Vertex* dest) {
    if (dest->dist == INF) return;  // No path available

    vector<Edge> reversedList;
    for (; dest->id != source->id; dest = dest->path)
        reversedList.push_back(dest->pathEdge);

    for (int i = reversedList.size() - 1; i >= 0; --i)
        edges.push_back(reversedList[i]);
}

/**
 * Display All the Strongly Connected Components in the Graph using the Tarjan Algorithm
 */
void Graph::displaySccTarjan() {
    stack<int> st;

    // Initialize disc, low and stackMember arrays
    for(Vertex* vertex : this->vertexSet) {
        vertex->disc = -1;
        vertex->low = -1;
        vertex->stackMember = false;
    }

    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (Vertex* vertex : vertexSet)
        if (vertex->disc == -1)
            sccTarjanUtil(vertex->id, st, true);
}

/**
 * Calculate the Strongly Connected Component to which the startingVertex Belongs
 * @param startingVertex
 */
void Graph::calculateSccTarjan(Vertex *startingVertex) {
    stack<int> st;

    // Initialize disc, low and stackMember arrays
    for(Vertex* vertex : this->vertexSet) {
        vertex->disc = -1;
        vertex->low = -1;
        vertex->stackMember = false;
    }

    int u = startingVertex->id;

    // The Bakery SSC will be stored on st
    sccTarjanUtil(u, st, false);
}

void Graph::sccTarjanUtil(int u, stack<int> &st, bool showResults) {
    // Static variable used for simplicity
    static int discoveryOrder = 0;

    Vertex* vertexU = this->vertexMap.at(u);

    // Initialize discovery time and low value
    vertexU->disc = vertexU->low = ++discoveryOrder;
    st.push(u);
    vertexU->stackMember = true;

    // Go through all vertices adjacent to this
    for(Edge &e: vertexU->adj) {
        Vertex* vertexAdj = e.dest;
        int vertexAdjID =vertexAdj->id;

        if(vertexAdj->disc == -1) {
            this->sccTarjanUtil(vertexAdjID, st, showResults);

            /* Check if the subtree rooted with 'vertexAdj' has a
             * connection to one of the ancestors of 'u'
            */
            vertexU->low = min(vertexU->low, vertexAdj->low);
        }

        /*
         * Update low value of 'u' only if 'vertexAdj' is still
         * in stack. (i.e it's a back edge, not cross edge).
         */
        else if (vertexAdj->stackMember)
            vertexU->low = min(vertexU->low, vertexAdj->disc);
    }

    // Head node found, pop the stack and print an SCC
    int w = 0;  // To store stack extracted vertices
    if(vertexU->low == vertexU->disc) {     // Head node of the SCC
        if(showResults) cout << "HEAD NODE: " << u << " SCC: ";
        while(st.top() != u) {  // Traverse the stack from the last element until the first of the SCC
            w = st.top();
            Vertex* currVertex = this->vertexMap.at(w);
            if(showResults) cout << w << " ";
            currVertex->stackMember = false;

            if(vertexU->disc == 1) currVertex->visited = true;

            st.pop();
        }
        w = st.top();
        Vertex* currVertex = this->vertexMap.at(w);
        if(showResults) cout << w << endl;
        currVertex->stackMember = false;
        if(vertexU->disc == 1) currVertex->visited = true;
        st.pop();
    }
}

bool Graph::getIsDirected() const {
    return isDirected;
}

void Graph::setIsDirected(bool isDirected) {
    Graph::isDirected = isDirected;
}

graphCities Graph::getCity() const {
    return city;
}

void Graph::setCity(graphCities city) {
    Graph::city = city;
}
