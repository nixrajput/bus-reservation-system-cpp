#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>

#include "Bus.h"
#include "utils.h"

// RESERVATION CLASS
class Reservation
{
private:
    char name[20], pnrNo[10], date[20];
    Bus bus;

public:
    // Constructor
    Reservation();

    // Methods
    void _generateTicket(char *, Bus);
    void _displayReservationDetails();
    void bookTicket();
    void viewReservations();
    void cancelReservation();
    void editReservation();
    void viewReservationByPNR();
    void viewReservationsByName();
    void viewReservationsByBusNo();
    void viewReservationsBySource();
    void viewReservationsByDestination();

    // Getters
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

    // Setters
    void setName(char *n)
    {
        if (n && n[0])
            strlcpy(name, n);
    }
};

#endif // !RESERVATION_H
