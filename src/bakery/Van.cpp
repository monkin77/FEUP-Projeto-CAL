//
// Created by bruno on 01/05/2021.
//

#include "Van.h"

template<class T>
Van<T>::Van(int totalBread, const Time &deliveryTime) : totalBread(totalBread), deliveryTime(deliveryTime) {
    deliveredBread = 0;
    totalTime = Time(0);
    totalDelay = Time(0);
}

template<class T>
void Van<T>::addClient(Client<T>& c) {
    clients.push_back(c);
}

template<class T>
void Van<T>::addEdge(Edge<T> &e) {
    edges.push_back(e);
}

template<class T>
void Van<T>::makeDelivery(Time travelTime, Time delay, int breadNum) {
    totalTime = totalTime + deliveryTime + travelTime;
    totalDelay = totalDelay + delay;
    deliveredBread += breadNum;
}

template<class T>
int Van<T>::getTotalBread() const {
    return totalBread;
}

template<class T>
int Van<T>::getDeliveredBread() const {
    return deliveredBread;
}

template<class T>
const Time &Van<T>::getDeliveryTime() const {
    return deliveryTime;
}

template<class T>
const Time &Van<T>::getTotalTime() const {
    return totalTime;
}

template<class T>
const Time &Van<T>::getTotalDelay() const {
    return totalDelay;
}

template<class T>
const vector <Client<T>> &Van<T>::getClients() const {
    return clients;
}

template<class T>
const vector <T> &Van<T>::getEdges() const {
    return edges;
}

template<class T>
int Van<T>::getLeftovers() const {
    return totalBread - deliveredBread;
}
