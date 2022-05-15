#include "Date.h"

Date::Date() : year(2000), month(1), day(1), hour(0), minute(0) {}

Date::Date(const unsigned int _year, const unsigned int _month, const unsigned int _day, const unsigned int _hour, const unsigned int _minute) : Date()
{
        setYear(_year);
        setMonth(_month);
        setDay(_day);
        setHour(_hour);
        setMinute(_minute);
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

bool Date::isValid()
{
    if ((year < 2000 || year > 9999) || (month < 1 || month > 12) || (hour > 23) || (minute > 59))
    {
        return false;
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day < 1 || day > 31)
        {
            return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || day > 30)
        {
            return false;
        }
    }
    else if (month == 2)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            if (day < 1 || day > 29)
            {
                return false;
            }
        }
        else
        {
            if (day < 1 || day > 28)
            {
                return false;
            }
        }
    }

    return true;
}

bool Date::same_day(const Date &d)
{
    if ((year == d.year) && (month == d.month) && (day == d.day))
    {
        return true;
    }

    return false;
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

unsigned int Date::operator-(const Date &d)
{
    unsigned int difference = 0;
    if (d.minute > minute)
    {
        if (hour == 0)
        {
            return 0;
        }
        hour--;
        minute += 60;
    }
    difference = minute - d.minute;
    if (d.hour > hour)
    {
        return 0;
    }
    difference += (hour - d.hour) * 60;

    return difference;
}

std::istream &operator>>(std::istream &in, Date &d)
{
    do
    {
        std::cout << "Enter date (format: year month day hour minutes): ";
        in >> d.year >> d.month >> d.day >> d.hour >> d.minute;
        if (!d.isValid())
        {
            std::cout << "Invalid date! Try again" << std::endl;
        }
    } while (!d.isValid());
    
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
        os << '0' << d.minute << " ";
    }
    else
    {
        os << d.minute << " ";
    }

    return os;
}

Date& Date::increase() 
{
    setMinute(minute + 1);
	if(minute == 60) 
	{
		setMinute(0);
		setHour(hour + 1);
		if(hour == 24) 
		{
			setHour(0);
			setDay(day + 1);
			if(day == 29 && month == 2)
			{
				if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {}
				else 
				{
					setDay(1);
					setMonth(month + 1);
				}
			}
			if(day == 30 && month == 2)
			{
				if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
				{
					setDay(1);
					setMonth(month + 1);
				}
			}
			if(day == 31)
			{
				if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) 
				{
					setDay(1);
					setMonth(month + 1);
				}
			}
			if(day == 32)
			{
				if ((month == 1) || (month == 3) || (month == 5) || (month == 7) ||
					 	(month == 8) || (month == 10) || (month == 12)) 
				{
					setDay(1);
					setMonth(month + 1);
					if (month == 13) 
					{
						setMonth(1);
						setYear(year + 1);
					}
				}
			} 

		}
	}
    return *this;
}

