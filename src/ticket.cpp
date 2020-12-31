#include<iostream>

#include "ticket.h"

using namespace std;

void Ticket::generateTicket(char cname[], Admin ab)
    {
        strcpy(name,cname);
        a = ab;
    }

void Ticket::displayTicket()
    {
        cout<<"\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout <<"\t\t\t\t\t\t\t\t\t\tName: " << name;
        a.showTicket();

    }