#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>

#include "Calendar.h"
#include "Event.h"

void Calendar::copy(const Calendar& other)
{
	size = other.size;
	capacity = other.capacity;
	delete[] events;
	events = new Event[capacity];
	for (int i = 0; i < capacity; i++)
	{
		events[i] = other.events[i];
	}
}

void Calendar::clean()
{
	delete[] events;
}

void Calendar::resize()
{
	capacity = capacity * 2;
	Event* temp = new Event[capacity];
	for (int i = 0; i < size; i++) 
	{
		temp[i] = events[i];
	}
	delete[] events;
	events = temp;
}

Calendar::Calendar() : capacity(10), size(0)
{
	events = new Event[capacity];
}

Calendar::Calendar(const Calendar& other)
{
	copy(other);
}

Calendar& Calendar::operator=(const Calendar& other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}

	return *this;
}

Calendar::~Calendar()
{
	clean();
}

bool Calendar::free(Date& d)  
{
	for (int i = 0; i < size; i++)
	{
		if(events[i].getBegin() == d)
		{
			return false;
		}
		if((d > events[i].getBegin()) && (d < events[i].getEnd()))
		{
			return false;
		}
	}
	return true;
}

bool Calendar::overlap(Date b, Date e)  
{
	int duration = e - b;
	while(duration > 0)
	{
		if(free(b))
		{
			b.increase();
			duration--;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool Calendar::working_hours(Date d) 
{
	if((d.getHour() >= 8) && (d.getHour() <= 18))
	{
		return true;
	}
	return false;
}

bool Calendar::free_slot(Date& d1, Date& d2, int duration)
{
	int temp_duration = duration;
	Date start_date = d1;
	Date temp = d1;
	while((start_date < d2))
	{
		if(free(temp) && (temp < d2) && (start_date.same_day(temp)) && working_hours(temp) && working_hours(start_date)) 
		{
			if(temp_duration > 0)
			{
				temp.increase();
				temp_duration--;
			}
			else
			{
				std::cout << start_date << std::endl;
				return true;
			}	
		}
		else
		{
			temp = start_date.increase();
			temp_duration = duration;
			start_date = temp;
		}
	}
	std::cout << "No free time for this period." << std::endl;
	return false;
}

void Calendar::add(Event& e)
{
	if (size == capacity)
	{
		resize();
	}
	if(!overlap(e.getBegin(), e.getEnd()))
	{
		events[size] = e;
		size++;
		std::cout << "Event added successfully!" << std::endl;
	}
	else
	{
		std::cout << "Failed to add event! Another event is scheduled for given date and time!" << std::endl;
	}
	
}

void Calendar::remove(const char* str, const Date& d)
{
	if (size == 0)
	{
		std::cout << "There are no events in your calendar!" << std::endl;
		return;
	}
	for (int i = 0; i < size; i++) 
    {
		char* output = nullptr;
		output = strstr(events[i].getName(), str);
		if ((output) && (events[i].getBegin() == d))
		{
			for (int j = i; j < size - 1; j++)
			{
				events[j] = events[j + 1];
			}
			size--;
			std::cout << "Event removed successfully!" << std::endl;
			return;
		}
	}
	std::cout << "Event not found!" << std::endl;
	return;
}

void Calendar::daily(Date& d)
{
  	int daily_tasks = 0;
  	Event* daily = new Event[size];
  	if (d.isValid() == true) 
  	{
    	for (int i = 0; i < size; i++) 
    	{
			if (events[i].getBegin().same_day(d))
			{  
				daily[daily_tasks] = events[i];
				daily_tasks++;
			}
    	}
    	if (daily_tasks == 0) 
		{
      		std::cout << "No tasks for this date!" << std::endl;
    	}
		else 
		{
			for (int i = 0; i < daily_tasks; i++) 
			{
				for (int j = 0; j < daily_tasks - i - 1; j++) 
				{
					if (daily[j] > daily[j + 1]) 
					{
						Event temp = daily[j];
						daily[j] = daily[j + 1];
						daily[j + 1] = temp;
					}
				}
    		}
			for (int i = 0; i < daily_tasks; i++) 
			{
				std::cout << daily[i] << std::endl;
			}
		}
  	}
  	else
  	{
   		std::cout << "Wrong date!" << std::endl;
  	}

	delete[] daily;
}

void Calendar::search(const char* str)
{
	for (int i = 0; i < size; i++) 
    {
		char* output = nullptr;
		output = strstr(events[i].getName(), str);
		if(output) 
		{
			std::cout << events[i] << std::endl;
		}
		else 
		{
			output = strstr(events[i].getComment(), str);
			if(output) 
			{
				std::cout << events[i] << std::endl;
			}
		}
	}
}

void Calendar::edit(const char* str, const Date& d)
{
	for (int i = 0; i < size; i++) 
    {
		char* output = nullptr;
		output = strstr(events[i].getName(), str);
		if ((output) && (events[i].getBegin() == d))
		{
			events[i] = Event();
			Event new_event;
			do
			{
				std::cin >> new_event;
				if (overlap(new_event.getBegin(), new_event.getEnd()))
				{
					std::cout << "Failed to edit the event! Another event is scheduled for given date and time!" << std::endl;
				}
			} while (overlap(new_event.getBegin(), new_event.getEnd()));

			events[i] = new_event;
			std::cout << "Event edited successfully!" << std::endl;
			return;
		}
	}
	std::cout << "Event not found!" << std::endl;
	return;
}

void Calendar::stat(Date d_begin, Date d_end) 
{
	char* filename = new char[20];
    std::stringstream tm;
    tm << "stats-";
    tm <<  d_begin.getYear() << '-';
    if (d_begin.getMonth() < 10)
    {
        tm << '0' << d_begin.getMonth() << '-';
    }
    else
    {
        tm <<  d_begin.getMonth() << '-';
    }
    if (d_begin.getDay() < 10)
    {
        tm << '0' << d_begin.getDay() << ".txt";
    }
    else
    {
        tm <<  d_begin.getDay() << ".txt";
    }

    strcpy(filename, tm.str().c_str());
    std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Could not open file" << std::endl;
		return;
	}
	
	Date* days = new Date[size];
	int index = 0;
	int* day_time = new int[size];
	for (int i = 0; i < size; i++)
	{
		day_time[i] = 0;
	}
	Date current_day;
	for (int i = 0 ; i < size; i++) 
	{
		if (((events[i].getBegin() > d_begin) || (events[i].getBegin() == d_begin)) && ((events[i].getBegin() < d_end) || (events[i].getBegin() == d_end)))
		{
			current_day = events[i].getBegin();
			bool exist = false;
			for (int j = 0; j < size; j++) 
			{
				if ((days[j].getYear() == current_day.getYear()) && (days[j].getMonth() == current_day.getMonth()) && (days[j].getDay() == current_day.getDay()))
				{
					exist = true;
					int sum = (events[i].getEnd() - events[i].getBegin());
					day_time[j] += sum;
					break;
				}
			}
			if (!exist) 
			{
				days[index] = current_day;
				int sum = (events[i].getEnd() - events[i].getBegin());
				day_time[index] += sum;
				index++;
			}
		}
	}
	for (int i = 0; i < index; i++) 
	{
		for (int j = 0; j < index - i - 1; j++) {
			if (day_time[j] < day_time[j + 1]) {
				int temp_int = day_time[j];
				day_time[j] = day_time[j+1];
				day_time[j+1] = temp_int;
				Date temp = days[j];
				days[j] = days[j + 1];
				days[j + 1] = temp;
			}
		}
    }
	for (int i = 0; i < index; i++) 
	{
		file << days[i].getDay() << "." << days[i].getMonth() << "." << days[i].getYear();
		file << " Busy time: " << day_time[i];
		file << std::endl;
	}
	file.close();
	delete[] days; 
	delete[] day_time;
	delete[] filename;
}

void Calendar::export_to_file() 
{
	std::ofstream file("my_calendar.txt");
	if (!file.is_open())
	{
		std::cout << "Could not open file" << std::endl;
		return;
	}
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size - i - 1; j++) 
		{
			if (events[j] > events[j + 1]) 
			{
				Event temp = events[j];
				events[j] = events[j + 1];
				events[j + 1] = temp;
			}
		}
    }
	for (int i = 0; i < size; i++) 
	{
		file << events[i] << std::endl;
		file << std::endl;
	}
	file.close();
}

std::ostream& operator<<(std::ostream& os, const Calendar& c)
{
	for (int i = 0; i < c.size; i++)
	{
		os << c.events[i] << std::endl;
	}

	return os;
}
