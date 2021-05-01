//
// Created by bruno on 01/05/2021.
//

#ifndef FEUP_PROJETO_CAL_POSITION_H
#define FEUP_PROJETO_CAL_POSITION_H

#include <math.h>

class Position {
private:
    double latitude, longitude;
public:
    Position(double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;

    double distance(const Position& p2);
};


#endif //FEUP_PROJETO_CAL_POSITION_H
