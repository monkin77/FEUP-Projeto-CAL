//
// Created by bruno on 01/05/2021.
//

#include "Position.h"

using namespace std;

Position::Position(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

double Position::getLatitude() const {
    return latitude;
}

double Position::getLongitude() const {
    return longitude;
}

double Position::distance(const Position &p2) {
    return sqrt(pow(this->latitude - p2.getLatitude(), 2) + pow(this->longitude - p2.getLongitude(), 2));
}
