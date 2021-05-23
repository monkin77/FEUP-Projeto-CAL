#include "Client.h"

Client::Client(int id, const string &name, Vertex* vertex, const Time &scheduledTime, int breadQuantity) {
    this->id = id;
    this->name = name;
    this->vertex = vertex;
    this->scheduledTime = scheduledTime;
    this->breadQuantity = breadQuantity;
    this->realTime = Time(0);
    this->allocated = false;
}

int Client::getId() const {
    return id;
}

const string &Client::getName() const {
    return name;
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

Vertex *Client::getVertex() const {
    return this->vertex;
}

const Time &Client::getRealTime() const {
    return realTime;
}

bool Client::isAllocated() const {
    return allocated;
}

void Client::setAllocated(bool allocated) {
    Client::allocated = allocated;
}

void Client::setBreadQuantity(int breadQuantity) {
    Client::breadQuantity = breadQuantity;
}

void Client::setVertex(Vertex *vertex) {
    Client::vertex = vertex;
}
