//
// Created by bruno on 01/05/2021.
//

#include "Client.h"

Client::Client(int id, const string &name, const Vertex &address, const Time &scheduledTime, int breadQuantity) {
    this->id = id;
    this->name = name;
    this->address = address;
    this->scheduledTime = scheduledTime;
    this->breadQuantity = breadQuantity;
    this->realTime = Time(0);
}

int Client::getId() const {
    return id;
}

const string &Client::getName() const {
    return name;
}

const Vertex &Client::getAddress() const {
    return address;
}

const Time &Client::getDeliveryTime() const {
    return scheduledTime;
}

int Client::getBreadQuantity() const {
    return breadQuantity;
}

void Client::setRealTime(const Time &realTime) {
    Client::realTime = realTime;
}
