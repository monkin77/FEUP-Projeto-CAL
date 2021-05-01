//
// Created by bruno on 01/05/2021.
//

#include "Time.h"

Time::Time(int hour, int minute) : hour(hour), minute(minute) {
    // TODO EXCEPTIONS IF TIME IS NOT VALID
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
