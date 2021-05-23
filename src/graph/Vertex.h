#ifndef FEUP_PROJETO_CAL_VERTEX_H
#define FEUP_PROJETO_CAL_VERTEX_H

#include <vector>

#include "Edge.h"
#include "../utils/MutablePriorityQueue.h"
#include "../utils/Position.h"

using namespace std;

class Client;   // Forward declaration

class Vertex {
    int id;
    Position info;  // content of the vertex (position)
    Client* client;

    std::vector<Edge > adj;		// outgoing edges

    int dist = 0;
    Vertex *path = nullptr;
    Edge pathEdge;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    bool visited = false;		// auxiliary field
    bool backwardsVisited = false;  // auxiliary field for bidirectional Dijkstra

    void addEdge(Vertex *dest, int w);

    // Tarjan SCC Algorithm Variables
    int disc = -1;
    int low = -1;
    bool stackMember = false;
public:
    static int nextID;
    Vertex(Position in);
    Vertex(int id, Position in);
    Vertex() {this->info = Position();};

    int getId() const;
    const vector<Edge> &getAdj() const;
    Position getPosition() const;
    int getDist() const;
    Vertex *getPath() const;
    Client *getClient() const;

    bool operator<(Vertex & vertex) const;

    void setClient(Client *client);

    // required by MutablePriorityQueue
    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
    friend class Bakery;
};


#endif //FEUP_PROJETO_CAL_VERTEX_H
