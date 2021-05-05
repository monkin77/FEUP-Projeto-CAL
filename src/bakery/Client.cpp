//
// Created by bruno on 01/05/2021.
//

#include "Client.h"

Client::Client(int id, const string &name, const Position &position, const Time &scheduledTime, int breadQuantity) {
    this->id = id;
    this->name = name;
    this->position = position;
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

const Position &Client::getPosition() const {
    return position;
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
