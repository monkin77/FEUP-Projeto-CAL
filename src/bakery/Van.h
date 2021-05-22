//
// Created by bruno on 01/05/2021.
//

#ifndef FEUP_PROJETO_CAL_VAN_H
#define FEUP_PROJETO_CAL_VAN_H


#include "../utils/Time.h"
#include "../graph/Edge.h"
#include "Client.h"
#include <vector>
#include <algorithm>

class Van {
private:
    int totalBread;
    int reservedBread;
    int deliveredBread;
    Time deliveryTime;
    Time totalTime;
    Time totalDelay;

    // these containers might become HashMaps
    vector<Client *> clients;
    vector<Edge> edges;
public:
    Van(int totalBread, const Time &deliveryTime);

    int getTotalBread() const;
    int getDeliveredBread() const;
    int getLeftovers() const;
    const Time &getDeliveryTime() const;
    const Time &getTotalTime() const;
    const Time &getTotalDelay() const;
    vector<Client *> &getClients();
    vector<Edge> &getEdges();

    int getReservedBread() const;

    void addTime(Time time);

    void setClients(const vector<Client *> &clients);
    void sortClientsByTime();

    void addClient(Client* c);
    void removeClient(Client* c);
    void addEdge(Edge& e);

    void makeDelivery(Time travelTime, Time delay, int breadNum);
    int getAvailableBread();
    Client* getWorstClientInRange(int maxBreadRange, int &clientCost);
};


#endif //FEUP_PROJETO_CAL_VAN_H
