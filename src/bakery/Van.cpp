//
// Created by bruno on 01/05/2021.
//

#include "Van.h"

Van::Van(int totalBread, const Time &deliveryTime) : totalBread(totalBread), deliveryTime(deliveryTime) {
    deliveredBread = 0;
    totalTime = Time(0);
    totalDelay = Time(0);
}

void Van::addClient(Client& c) {
    clients.push_back(c);
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

const vector <Client> &Van::getClients() const {
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
