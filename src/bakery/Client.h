//
// Created by bruno on 01/05/2021.
//

#ifndef FEUP_PROJETO_CAL_CLIENT_H
#define FEUP_PROJETO_CAL_CLIENT_H

#include <string>
#include "../graph/Vertex.h"
#include "../utils/Time.h"

using namespace std;

class Client {
private:
    int id;
    string name;
    Vertex address;
    Time scheduledTime;
    Time realTime;
    int breadQuantity;
public:
    Client(int id, const string &name, const Vertex &address, const Time &scheduledTime, int breadQuantity);

    int getId() const;
    const string &getName() const;
    const Vertex &getAddress() const;
    const Time &getDeliveryTime() const;
    int getBreadQuantity() const;

    void setRealTime(const Time &realTime);
};


#endif //FEUP_PROJETO_CAL_CLIENT_H
