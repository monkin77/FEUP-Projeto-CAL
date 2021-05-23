#include <fstream>
#include <bits/stdc++.h>

#include "GraphBuilder.h"

using namespace std;

void defaultGraphBuilder(Graph &G){
    G.addVertex(0, Position(1, 1));
    G.addVertex(1, Position(2, 2));
    G.addVertex(2, Position(3, 3));
}

bool readGraphFromFile(Graph &G, string directoryName, bool isStrongComponent) {
    string nodesFile, edgesFile;
    if(!isStrongComponent) {
        nodesFile = directoryName + "/nodes.txt";
        edgesFile = directoryName + "/edges.txt";
    } else {
        nodesFile = directoryName + "/strongNodes.txt";
        edgesFile = directoryName + "/strongEdges.txt";
    }

    ifstream fin;

    // READ NODES

    fin.open(nodesFile);

    if(!fin.is_open())
        return false;

    string line;
    char token;

    int numNodes;
    fin >> numNodes;
    getline(fin, line);   // read new line character (trash)

    for(int i = 0; i < numNodes; i++) {
        getline(fin, line);
        stringstream ss(line);

        int id;
        double latitude, longitude;
        ss >> token >> id >> token >> latitude >> token >> longitude;

        G.addVertex(id, Position(latitude, longitude));
    }

    fin.close();

    // READ EDGES

    fin.open(edgesFile);

    if(!fin.is_open())
        return false;

    int numEdges;
    fin >> numEdges;
    getline(fin, line);   // read new line character (trash)

    for(int i = 0; i < numEdges; i++) {
        getline(fin, line);
        stringstream ss(line);

        int idNodeOrig, idNodeDest;
        ss >> token >> idNodeOrig >> token >> idNodeDest;

        if(idNodeOrig != idNodeDest)    // Avoid having edges that point to itself
            G.addEdge(idNodeOrig, idNodeDest, 1);   // add edge with unitary weight
    }

    fin.close();

    return true;
}
