#include "Date.h"

Date::Date() : year(2000), month(1), day(1), hour(0), minute(0) {}

Date::Date(const unsigned int _minute, const unsigned int _hour, const unsigned int _day, const unsigned int _month, const unsigned int _year)
{
    setMinute(_minute);
    setHour(_hour);
    setMonth(_month);
    setYear(_year);
    setDay(_day);
}

void Date::setYear(const unsigned int _year)
{
    if (_year < 2000 || _year > 9999) 
    {
        std::cout << "Wrong year! Try again..." << std::endl;
        return;
    }

    if (check(day, month, _year))
    {
        year = _year;
    }

}

void Date::setMonth(const unsigned int _month)
{
    if (_month < 1 || _month > 12)
    {
        std::cout << "Wrong month! Try again..." << std::endl;
        return;
    }

    if (check(day, _month, year))
    {
        month = _month;
    }

}

void Date::setDay(const unsigned int _day)
{
    if (check(_day, month, year))
    {
        day = _day;
    }

}

void Date::setHour(const unsigned int _hour)
{
    if (_hour > 23)
    {
        std::cout << "Wrong hour! Try again..." << std::endl;
        return;
    }

    hour = _hour;
}

void Date::setMinute(const unsigned int _minute)
{
    if (_minute > 59)
    {
        std::cout << "Wrong minute! Try again..." << std::endl;
        return;
    }

    minute = _minute;
}

bool Date::check(const unsigned int _day, const unsigned int _month, const unsigned int _year)
{
    if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12)
    {
        if (_day < 1 || _day > 31)
        {
            std::cout << "Wrong day! Try again..." << std::endl;
            return false;
        }
    }
    else if (_month == 4 || _month == 6 || _month == 9 || _month == 11)
    {
        if (_day < 1 || _day > 30)
        {
            std::cout << "Wrong day! Try again..." << std::endl;
            return false;
        }
    }
    else if (_month == 2)
    {
        if (_year % 4 == 0)
        {
            if (_year % 100 == 0)
            {
                if (_year % 400 == 0)
                {
                    if (_day < 1 || _day > 29)
                    {
                        std::cout << "Wrong day! Try again..." << std::endl;
                        return false;
                    }
                }
                else
                {
                    if (_day < 1 || _day > 28)
                    {
                        std::cout << "Wrong day! Try again..." << std::endl;
                        return false;
                    }
                }
            }
            else
            {
                if (_day < 1 || _day > 29)
                {
                    std::cout << "Wrong day! Try again..." << std::endl;
                    return false;
                }
            }
        }
        else
        {
            if (_day < 1 || _day > 28)
            {
                std::cout << "Wrong day! Try again..." << std::endl;
                return false;
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
    } while (d.year < 2000 || d.year > 9999);

    do
    {
        std::cout << "Month: ";
        in >> d.month;
    } while (d.month < 1 || d.month > 12);

    do
    {
        std::cout << "Day: ";
        in >> d.day;
    } while (!d.check(d.day, d.month, d.year));

    do
    {
        std::cout << "Hour: ";
        in >> d.hour;
    } while (d.hour > 23);

    do
    {
        std::cout << "Minute: ";
        in >> d.minute;
    } while (d.minute > 59);

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
