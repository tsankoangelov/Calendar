#include "Date.h"

Date::Date() : year(2000), month(1), day(1), hour(0), minute(0) {}

Date::Date(const unsigned int _year, const unsigned int _month, const unsigned int _day, const unsigned int _hour, const unsigned int _minute)
{
    if(isValid(_year, _month, _day, _hour, _minute))
    {
        setYear(_year);
        setMonth(_month);
        setDay(_day);
        setHour(_hour);
        setMinute(_minute);
    }
    else
    {
        std::cout << "Wrong date! Try again!" << std::endl;
    }
}

void Date::setYear(const unsigned int _year)
{
    year = _year;
    
}

void Date::setMonth(const unsigned int _month)
{
    month = _month;
}

void Date::setDay(const unsigned int _day)
{
    day = _day;
}

void Date::setHour(const unsigned int _hour)
{
    hour = _hour;
}

void Date::setMinute(const unsigned int _minute)
{
    minute = _minute;
}

bool Date::isValid(const unsigned int _year, const unsigned int _month, const unsigned int _day, const unsigned int _hour, const unsigned int _minute)
{
    if (_year < 2000 || _year > 9999)
    {
        std::cout << "Wrong date! Try again!" << std::endl;
        return false;
    }

    if (_month < 1 || _month > 12)
    {
        std::cout << "Wrong date! Try again!" << std::endl;
        return false;
    }

    if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12)
    {
        if (_day < 1 || _day > 31)
        {
            std::cout << "Wrong date! Try again!" << std::endl;
            return false;
        }
    }
    else if (_month == 4 || _month == 6 || _month == 9 || _month == 11)
    {
        if (_day < 1 || _day > 30)
        {
            std::cout << "Wrong date! Try again!" << std::endl;
            return false;
        }
    }
    else if (_month == 2)
    {
        if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0))
        {
            if (_day < 1 || _day > 29)
            {
                std::cout << "Wrong date! Try again!" << std::endl;
                return false;
            }
        }
        else
        {
            if (_day < 1 || _day > 28)
            {
                std::cout << "Wrong date! Try again!" << std::endl;
                return false;
            }
        }
    }

    if (_hour > 23)
    {
        std::cout << "Wrong date! Try again!" << std::endl;
        return false;
    }

    if (_minute > 59)
    {
        std::cout << "Wrong date! Try again!" << std::endl;
        return false;
    }

    return true;
}

bool Date::operator==(const Date &d)
{
    if ((year == d.year) && (month == d.month) && (day == d.day) && (hour == d.hour) && (minute == d.minute))
    {
        return true;
    }

    return false;
}

bool Date::operator>(const Date &d)
{
    if (year < d.year)
    {
        return false;
    }
    if (year == d.year)
    {
        if (month < d.month)
        {
            return false;
        }
        if (month == d.month)
        {
            if (day < d.day)
            {
                return false;
            }
            if (day == d.day)
            {
                if (hour < d.hour)
                {
                    return false;
                }
                if (hour == d.hour)
                {
                    if (minute <= d.minute)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool Date::operator<(const Date &d)
{
    if (year > d.year)
    {
        return false;
    }
    if (year == d.year)
    {
        if (month > d.month)
        {
            return false;
        }
        if (month == d.month)
        {
            if (day > d.day)
            {
                return false;
            }
            if (day == d.day)
            {
                if (hour > d.hour)
                {
                    return false;
                }
                if (hour == d.hour)
                {
                    if (minute >= d.minute)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

std::istream &operator>>(std::istream &in, Date &d)
{
    do
    {
        std::cout << "Year: ";
        in >> d.year;
        std::cout << "Month: ";
        in >> d.month;
        std::cout << "Day: ";
        in >> d.day;
        std::cout << "Hour: ";
        in >> d.hour;
        std::cout << "Minute: ";
        in >> d.minute;
    } while (!d.isValid(d.year, d.month, d.day, d.hour, d.minute));
    
    return in;
}

std::ostream &operator<<(std::ostream &os, const Date &d)
{
    if (d.day < 10)
    {
        os << '0' << d.day << '.';
    }
    else
    {
        os << d.day << '.';
    }

    if (d.month < 10)
    {
        os << '0' << d.month << '.';
    }
    else
    {
        os << d.month << '.';
    }

    os << d.year << ' ';

    if (d.hour < 10)
    {
        os << '0' << d.hour << ':';
    }
    else
    {
        os << d.hour << ':';
    }

    if (d.minute < 10)
    {
        os << '0' << d.minute << std::endl;
    }
    else
    {
        os << d.minute << std::endl;
    }

    return os;
}
