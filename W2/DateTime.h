#ifndef DATETIME_H
#define DATETIME_H

#include <string>

class DateTime
{
private:
    int year, month, day, hour, minute, second;

public:
    // Default constructor
    DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

    // Constructor with parameters to initialize the year, month, day, hour, minute, and second
    DateTime(
        int year, int month, int day, int hour, int minute, int second
        ) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

    // Constructor with a string parameter to initialize the year, month, day, hour, minute, and second
    DateTime(std::string dateTimeString);

    void printDateTime();
    bool operator<(const DateTime &other);
};

#endif