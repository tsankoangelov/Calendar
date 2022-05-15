#ifndef __Date_HPP
#define __Date_HPP

/**
 * @file Date.h
 * @author Tsanko Angelov
 * @brief Class Date implements date
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>

class Date
{
private:
	unsigned int year, month, day, hour, minute;

public:
	Date();
	Date(const unsigned int, const unsigned int, const unsigned int, const unsigned int, const unsigned int);

	void setYear(const unsigned int);
	void setMonth(const unsigned int);
	void setDay(const unsigned int);
	void setHour(const unsigned int);
	void setMinute(const unsigned int);

	unsigned int getYear() const { return this->year; }
	unsigned int getMonth() const { return this->month; }
	unsigned int getDay() const { return this->day; }
	unsigned int getHour() const { return this->hour; }
	unsigned int getMinute() const { return this->minute; }

    	bool isValid();
	bool same_day(const Date&);
	Date& increase();

	bool operator==(const Date&);
	bool operator>(const Date&);
	bool operator<(const Date&);
	unsigned int operator-(const Date&);
	 
	friend std::ostream& operator<<(std::ostream&,const Date&);
    	friend std::istream& operator>>(std::istream&, Date&);


};

#endif
