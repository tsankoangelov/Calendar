#ifndef __Event_HPP
#define __Event_HPP

#include "Date.h"

class Event
{
private:
	char* name;
	char* comment;
	Date begin;
	Date end;

	void copy(const Event&);
	void clean();

public:
	Event();
	Event(const Event&);
	Event& operator=(const Event&);
	~Event();

	Event(const char*, const char*, const Date&, const Date&);

	void setName(const char*);
	void setComment(const char*);
	void setBegin(const Date&);
	void setEnd(const Date&);

	char* getName() const { return this->name; }
	char* getComment() const { return this->comment; }
	Date getBegin() const { return this->begin; }
	Date getEnd() const { return this->end; }

	bool check_period();

	bool operator==(const Event&);
	bool operator>(const Event&);
	bool operator<(const Event&);

        friend std::istream& operator>>(std::istream&, Event&);
	friend std::ostream& operator<<(std::ostream&, const Event&);
};



#endif
