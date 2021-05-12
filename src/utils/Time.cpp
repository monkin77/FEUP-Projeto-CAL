//
// Created by bruno on 01/05/2021.
//

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
 * Calculate the difference between two times, in minutes
 * Note that this can return a negative time
 */
int Time::operator-(const Time &t2) const {
    return this->toMinutes() - t2.toMinutes();
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
    os << "hour: " << time.hour << " minute: " << time.minute;
    return os;
}
