#include "DateTime.h"

#include <iostream>
#include <sstream>

DateTime::DateTime(std::string dateTimeString)
{

    std::string dateString, timeString;
    std::stringstream ss(dateTimeString);
    std::getline(ss, dateString, ' ');
    std::getline(ss, timeString);

    std::string _year, _month, _day, _hour, _min, _sec;

    std::stringstream ss1(dateString);
    std::getline(ss1, _year, '-');
    std::getline(ss1, _month, '-');
    std::getline(ss1, _day);

    year = stoi(_year);
    month = stoi(_month);
    day = stoi(_day);

    std::stringstream ss2(timeString);
    std::getline(ss2, _hour, ':');
    std::getline(ss2, _min, ':');
    std::getline(ss2, _sec);

    hour = stoi(_hour);
    minute = stoi(_min);
    second = stoi(_sec);
}
void DateTime::printDateTime()
{
    std::cout << year << "/"
              << (month < 10 ? "0" : "") << month << "/"
              << (day < 10 ? "0" : "") << day << " "
              << (hour < 10 ? "0" : "") << hour << ":"
              << (minute < 10 ? "0" : "") << minute << ":"
              << (second < 10 ? "0" : "") << second << std::endl;
}
bool DateTime::operator<(const DateTime &other)
{
    if (year < other.year)
        return true;
    else if (year == other.year)
    {
        if (month < other.month)
            return true;
        else if (month == other.month)
        {
            if (day < other.day)
                return true;
            else if (day == other.day)
            {
                if (hour < other.hour)
                    return true;
                else if (hour == other.hour)
                {
                    if (minute < other.minute)
                        return true;
                    else if (minute == other.minute)
                    {
                        if (second < other.second)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
