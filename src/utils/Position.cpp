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

bool Position::operator==(const Position &rhs) const {
    return latitude == rhs.latitude &&
           longitude == rhs.longitude;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

ostream &operator<<(ostream &os, const Position &position) {
    os << "(" << position.latitude << ", " << position.longitude << ")";
    return os;
}

