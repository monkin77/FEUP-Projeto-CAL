//
// Created by bruno on 01/05/2021.
//

#ifndef FEUP_PROJETO_CAL_TIME_H
#define FEUP_PROJETO_CAL_TIME_H


class Time {
private:
    int hour, minute;
public:
    Time();
    Time(int minutes);
    Time(int hour, int minute);
    Time(const Time &time);

    int getHour() const;
    int getMinute() const;

    void addMinutes(int mins);
    int toMinutes() const;

    Time operator+(const Time& t2) const;
    int operator-(const Time& t2) const;
    bool operator<(const Time& t2) const;
};


#endif //FEUP_PROJETO_CAL_TIME_H
