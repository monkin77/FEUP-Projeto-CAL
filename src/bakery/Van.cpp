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

const vector <Client *> &Van::getClients() const {
    return clients;
}

const vector<Edge> &Van::getEdges() const {
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

Client *Van::removeFarthestClientInRange(int maxBreadRange) {
    int chosen = -1;
    int maxDistance = 0;
    for (int i = 0; i < clients.size(); ++i) {
        Client* client = clients[i];
        if (client->getBreadQuantity() > maxBreadRange) continue;
        int dist = 0;
        for (Client *client2 : clients) {
            if (client->getId() == client2->getId()) continue;
            dist += client->getVertex()->getPosition().distance(client2->getVertex()->getPosition());
        }
        if (dist > maxDistance) {
            maxDistance = dist;
            chosen = i;
        }
    }
    if (chosen == -1) return NULL;
    Client* result = clients[chosen];
    reservedBread -= result->getBreadQuantity();
    clients.erase(clients.begin() + chosen);
    return result;
}

int Van::getReservedBread() const {
    return reservedBread;
}
