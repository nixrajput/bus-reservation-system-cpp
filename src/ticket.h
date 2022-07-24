#ifndef TICKET_H
#define TICKET_H

#include <iostream>

#include "bus.h"

// CLASS TICKET
class Ticket
{
private:
    char name[20], pnrNo[10], date[20];
    Bus bus;

public:
    void generateTicket(char *, Bus);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByBus();
    void showTicketsBySource();
    void showTicketsByDestination();
    void showAllTickets();

    // GETTERS
    char *getName()
    {
        return name;
    }

    char *getPnrNo()
    {
        return pnrNo;
    }

    char *getDate()
    {
        return date;
    }

    // SETTERS
    void setName(char *n)
    {
        if (n && n[0])
            strcpy(name, n);
    }
};
#endif // !TICKET_H
