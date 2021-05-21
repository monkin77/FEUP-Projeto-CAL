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
    Vertex* vertex;
    Time scheduledTime;
    Time realTime;
    int breadQuantity;
    bool allocated;
public:
    Client(int id, const string &name, Vertex* vertex, const Time &scheduledTime, int breadQuantity);

    int getId() const;
    const string &getName() const;
    Vertex* getVertex() const;
    const Time &getDeliveryTime() const;
    int getBreadQuantity() const;

    const Time &getRealTime() const;

    void setRealTime(const Time &realTime);

    void setBreadQuantity(int breadQuantity);

    bool isAllocated() const;

    void setAllocated(bool allocated);
};


#endif //FEUP_PROJETO_CAL_CLIENT_H
