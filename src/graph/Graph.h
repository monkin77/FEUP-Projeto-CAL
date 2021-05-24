#ifndef FEUP_PROJETO_CAL_GRAPH_H
#define FEUP_PROJETO_CAL_GRAPH_H

#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <stack>

#include "Vertex.h"
#include "../utils/Position.h"
#include "../utils/Time.h"
#include "../bakery/Client.h"

using namespace std;

constexpr auto INF = std::numeric_limits<int>::max();

enum graphCities {Unknown, Penafiel, Porto, Espinho};

class Graph {
    unordered_map<int, Vertex*> vertexMap;
    vector<Vertex*> vertexSet;
    bool isDirected;

    void filterBySCC();
    void filterByRadius(Vertex* start, double radius);
    void analyzeConnectivity(Vertex* start);

    void DFSVisit(Vertex* v);
    bool relax(Vertex* v, Edge e);

    graphCities city;
public:
    Vertex* findVertex(const Position &inf) const;
    Vertex* findVertex(int idNode) const;

    vector<Vertex *> getVertexSet() const;
    int getNumVertex() const;

    bool addVertex(int id, const Position &in);
    bool addEdge(const Position &sourc, const Position &dest, int weight);
    bool addEdge(int idNodeOrig, int idNodeDest, int weight);

    void removeVertex(int id);

    void printGraph();

    void removeUnreachableVertexes(Vertex* start, double radius);

    void dijkstraShortestPath(Vertex *s);
    void dijkstraShortestPath(Vertex *s, Vertex* d);
    Client* dijkstraClosestClient(Vertex *s, vector<Vertex*> dests);

    // Bidirectional Dijkstra Methods
    int bidirectionalDijkstra(Vertex *s, Vertex *d);
    int joinBidirectionalDistances(Vertex* intersectionVertex, Vertex* oppDirectionVertex, int oppDirectionWeight);
    const Edge* findSymmetricEdge(Edge& e);
    void invertOppositeEdges(Vertex *oppositeStart, Edge& edge, Vertex* intersectionVertex, Vertex* lastVertex);

    void addPathToEdgeList(vector<Edge> &edges, Vertex* source, Vertex* dest);

    void displaySccTarjan();
    void calculateSccTarjan(Vertex* startingVertex);
    void sccTarjanUtil(int u, stack<int> &st, bool showResults);

    bool getIsDirected() const;

    void setIsDirected(bool isDirected);

    graphCities getCity() const;

    void setCity(graphCities city);
};


#endif //FEUP_PROJETO_CAL_GRAPH_H
