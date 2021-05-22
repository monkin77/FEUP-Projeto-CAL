#ifndef FEUP_PROJETO_CAL_POSITION_H
#define FEUP_PROJETO_CAL_POSITION_H

#include <math.h>
#include <string>
#include <ostream>

class Position {
private:
    double latitude, longitude;
public:
    Position(double latitude, double longitude);
    Position() {latitude = 0; longitude = 0;}

    double getLatitude() const;
    double getLongitude() const;

    double distance(const Position& p2);

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Position &position);
};



#endif
