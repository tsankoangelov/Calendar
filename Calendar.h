#ifndef __Calendar_HPP
#define __Calendar_HPP

/**
 * @file Calendar.h
 * @author Tsanko Angelov
 * @brief Class Calendar implements personal calendar
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Event.h"

class Calendar
{
private:
	Event* events;
	int capacity;
	int size;

	void copy(const Calendar&);
	void clean();
	void resize();

public:
	Calendar();
	Calendar(const Calendar&);
	Calendar& operator=(const Calendar&);
	~Calendar();

	Event* getEvents() const { return this->events;  }
	int getCapacity() const { return this->capacity; }
	int getSize() const { return this->size; }

	void add(Event&);
	void remove(const char* str, const Date& d);
	void daily(Date&);
	void search(const char*);
	void edit(const char* str, const Date& d);
	void stat(Date, Date);
	bool free(Date&);
	bool overlap(Date, Date);
	bool working_hours(Date); 
	bool free_slot(Date&, Date&, int);
	void export_to_file();


	friend std::ostream& operator<<(std::ostream&, const Calendar&);

};


#endif
