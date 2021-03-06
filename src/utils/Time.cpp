#include "Time.h"

Time::Time() {
    hour = 0;
    minute = 0;
}

Time::Time(int minutes) {
    hour = minutes / 60;
    minute = minutes % 60;
}

Time::Time(int hour, int minute) : hour(hour), minute(minute) {}

Time::Time(const Time &time) {
    this->hour = time.getHour();
    this->minute = time.getMinute();
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::toMinutes() const {
    return hour*60 + minute;
}

/**
 * Note that this can and will return a negative time
 */
Time Time::operator-(const Time &t2) const {
    return Time(this->toMinutes() - t2.toMinutes());
}

bool Time::operator<(const Time &t2) const {
    if (this->hour == t2.getHour())
        return this->minute < t2.getMinute();
    return this->hour < t2.getHour();
}

void Time::addMinutes(int mins) {
    minute += mins;
    hour += minute / 60;
    minute %= 60;
}

Time Time::operator+(const Time &t2) const {
    return Time(this->toMinutes() + t2.toMinutes());
}

std::ostream &operator<<(std::ostream &os, const Time &time) {
    os << time.hour << "h" << time.minute << "m";
    return os;
}
