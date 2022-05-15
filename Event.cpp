#include <cstring>

#include "Event.h"

void Event::copy(const Event &other)
{
	begin = other.begin;
	end = other.end;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	comment = new char[strlen(other.comment) + 1];
	strcpy(comment, other.comment);
}

void Event::clean()
{
	delete[] name;
	delete[] comment;
}

Event::Event()
{
	name = new char[9];
	strcpy(name, "No named");
	comment = new char[11];
	strcpy(comment, "No comment");
}

Event::Event(const Event &other)
{
	copy(other);
}

Event &Event::operator=(const Event &other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}

	return *this;
}

Event::~Event()
{
	clean();
}

Event::Event(const char* _name, const char* _comment, const Date& b, const Date& e) : Event()
{
	setName(_name);
	setComment(_comment);
	setBegin(b);
	setEnd(e);
}

void Event::setName(const char *_name)
{
	delete[] name;
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
}

void Event::setComment(const char *_comment)
{
	delete[] comment;
	comment = new char[strlen(_comment) + 1];
	strcpy(comment, _comment);
}

void Event::setBegin(const Date& d)
{
	begin = d;
}

void Event::setEnd(const Date& d)
{
	end = d;
}

bool Event::operator==(const Event &a)
{
	return begin == a.begin && end == a.end && strcmp(name, a.name) == 0 && strcmp(comment, a.comment) == 0;
}

bool Event::check_period()
{
	if ((end < begin) || (end - begin > 1440) || (!begin.same_day(end)))
	{
		return false;
	}

	return true;
}

bool Event::operator>(const Event &e)
{
	if(begin < e.begin)
	{
		return false;
	}

	return true;
}

bool Event::operator<(const Event &e)
{
	if(begin > e.begin)
	{
		return false;
	}

	return true;
}

std::istream &operator>>(std::istream &in, Event& e)
{
	do
	{
		in.getline(e.name, 100);
	} while (strlen(e.name) > 100);
	
	do
	{
		in.getline(e.comment, 500);
	} while (strlen(e.comment) > 500);
	
	do
	{
		in >> e.begin >> e.end;
		if (!e.begin.isValid())
        {
            std::cout << "Start date of the event is invalid! Try again" << std::endl;
        }
		if (!e.end.isValid())
        {
            std::cout << "End date of the event is invalid! Try again" << std::endl;
        }
		if (!e.check_period())
        {
            std::cout << "Invalid period for the event! Period can not be bigger than one day! Check start and end date and try again" << std::endl;
        }
	} while (!e.begin.isValid() || !e.end.isValid() || !e.check_period());
	
	return in;
}

std::ostream &operator<<(std::ostream &os,const Event& e)
{
	os << "Event: " << e.name << std::endl;
	os << "Comment: " << e.comment << std::endl;
	os << e.begin << "- " << e.end;

	return os;
}
