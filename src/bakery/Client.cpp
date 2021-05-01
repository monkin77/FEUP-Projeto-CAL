//
// Created by bruno on 01/05/2021.
//

#include "Client.h"

template<class T>
Client<T>::Client(int id, const string &name, const Vertex<T> &address, const Time &scheduledTime, int breadQuantity) {
    this->id = id;
    this->name = name;
    this->address = address;
    this->scheduledTime = scheduledTime;
    this->breadQuantity = breadQuantity;
    this->realTime = Time(0);
}

template<class T>
int Client<T>::getId() const {
    return id;
}

template<class T>
const string &Client<T>::getName() const {
    return name;
}

template<class T>
const Vertex<T> &Client<T>::getAddress() const {
    return address;
}

template<class T>
const Time &Client<T>::getDeliveryTime() const {
    return scheduledTime;
}

template<class T>
int Client<T>::getBreadQuantity() const {
    return breadQuantity;
}

template<class T>
void Client<T>::setRealTime(const Time &realTime) {
    Client::realTime = realTime;
}
