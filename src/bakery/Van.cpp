//
// Created by bruno on 01/05/2021.
//

#include "Van.h"

Van::Van(int totalBread, const Time &deliveryTime) : totalBread(totalBread), deliveryTime(deliveryTime) {
    deliveredBread = 0;
    reservedBread = 0;
    totalTime = Time(0);
    totalDelay = Time(0);
}

void Van::addClient(Client* c) {
    c->setAllocated(true);
    clients.push_back(c);
    reservedBread += c->getBreadQuantity();
}

void Van::addEdge(Edge &e) {
    edges.push_back(e);
}

void Van::makeDelivery(Time travelTime, Time delay, int breadNum) {
    totalTime = totalTime + deliveryTime + travelTime;
    totalDelay = totalDelay + delay;
    deliveredBread += breadNum;
}

int Van::getTotalBread() const {
    return totalBread;
}

int Van::getDeliveredBread() const {
    return deliveredBread;
}

const Time &Van::getDeliveryTime() const {
    return deliveryTime;
}

const Time &Van::getTotalTime() const {
    return totalTime;
}

const Time &Van::getTotalDelay() const {
    return totalDelay;
}

vector <Client *> &Van::getClients() {
    return clients;
}

vector<Edge> &Van::getEdges() {
    return edges;
}

int Van::getLeftovers() const {
    return totalBread - deliveredBread;
}

void Van::addTime(Time time) {
    totalTime = totalTime + time;
}

void Van::setClients(const vector<Client *> &clients) {
    Van::clients = clients;
}

void Van::sortClientsByTime() {
    sort(clients.begin(), clients.end(), [](const Client* c1, const Client* c2) -> bool {
        return c1->getDeliveryTime() < c2->getDeliveryTime();
    });
}

/**
 * Returns the client with the highest cost, where the breads ordered are less than the Van capacity
 * If none, returns NULL
 * @param maxBreadRange
 * @return Best Client Choice, NULL otherwise
 */
Client *Van::getWorstClientInRange(int maxBreadRange, int &clientCost) {
    Client* chosen = NULL;
    int maxCost = 0;
    for (int i = 0; i < clients.size(); ++i) {
        Client* client = clients[i];
        if (client->getBreadQuantity() > maxBreadRange) continue;
        int cost = 0;
        for (Client *client2 : clients) {
            if (client->getId() == client2->getId()) continue;
            cost += client->getVertex()->getPosition().distance(client2->getVertex()->getPosition());
            cost -= abs((client->getDeliveryTime() - client2->getDeliveryTime()).toMinutes());
        }
        if (cost > maxCost) {
            maxCost = cost;
            chosen = client;
        }
    }
    clientCost = maxCost;
    return chosen;
}

int Van::getReservedBread() const {
    return reservedBread;
}

int Van::getAvailableBread() {
    return totalBread - reservedBread;
}

void Van::removeClient(Client *c) {
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
        if ((*it)->getId() == c->getId()) {
            clients.erase(it);
            break;
        }
    reservedBread -= c->getBreadQuantity();
}
