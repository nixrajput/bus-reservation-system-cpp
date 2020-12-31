#ifndef TICKET_H
#define TICKET_H

#include<iostream>
#include "admin.h"

// CLASS TICKET
class Ticket
{
private:
    char name[50];
    Admin a;
public:
    void generateTicket(char*, Admin);
    void displayTicket();

    char* getName()
    {
        return name;
    }
};
#endif