#include<iostream>
#include<cstring>

#include "Calendar.h"

void CommandPromt()
{
    Calendar cal;
    char word[100];
    std::cout << "Welcome to your personal calendar! What do you need? " << std::endl;

    while(true)
    {
        std::cin.getline(word, 100);

        if (strcmp(word, "EXIT") == 0)
        {
            std::cout << "Have a nice day!" << std::endl;
            return;
        }
        else if (strcmp(word, "ADD") == 0)
        {
            std::cout << "Please type the information about your event!(name, comment, begin and end date)" << std::endl;
            Event e;
            std::cin >> e;
            cal.add(e);
            std::cin.ignore();
        }
        else if (strcmp(word, "REMOVE") == 0)
        {
            std::cout << "Please type the information about the event you want to remove!(name, comment, begin and end date)" << std::endl;
            Event e;
            std::cin >> e;
            cal.remove(e);
            std::cin.ignore();
        }
        else if (strcmp(word, "DAILY EVENTS") == 0)
        {
            std::cout << "Please enter date (year, month, day)" << std::endl;
            Date d;
            std::cin >> d;
            cal.daily(d);
            std::cin.ignore();
        }
        else if (strcmp(word, "EDIT") == 0)
        {
            std::cout << "Please type the information about the event you want to edit!(name, comment, begin and end date)" << std::endl;
            Event e;
            std::cin >> e;
            cal.edit(e);
            std::cin.ignore();
        }
        else if (strcmp(word, "SEARCH") == 0)
        {
            std::cout << "Search event by name or comment" << std::endl;
            char* s = new char[100];
            std::cin.getline(s, 100);
            cal.search(s);
            std::cin.ignore();

        }
        else if (strcmp(word, "STATISTIC") == 0)
        {
            std::cout << "Show statistic for given period" << std::endl;
            std::cout << "Please enter begin date of the period" << std::endl;
            Date begin;
            std::cin >> begin;
            std::cout << "Please enter end date of the period" << std::endl;
            Date end;
            std::cin >> end;
            cal.stat(begin, end);
        }
        else if (strcmp(word, "FREE SLOT") == 0)
        {
            std::cout << "Find free slot for given period for your event" << std::endl;
            std::cout << "Please enter begin date of the period" << std::endl;
            Date begin;
            std::cin >> begin;
            std::cout << "Please enter end date of the period" << std::endl;
            Date end;
            std::cin >> end;
            std::cout << "Please enter duration of your event" << std::endl;
            int duration;
            std::cin >> duration;
            cal.free_slot(begin, end, duration);
        }
        else
        {
            std::cout << "Invalid command! Try again!" << std::endl;
            strcpy(word, "");
        }
    }
}

int main()
{
    CommandPromt();

    return 0;
}