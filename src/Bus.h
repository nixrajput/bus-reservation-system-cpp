#ifndef BUS_H
#define BUS_H

#include <iostream>

#include "utils.h"

using namespace std;

// BUS CLASS
class Bus
{
private:
    // Variables
    int maxSeats, bookedSeats;
    double busFare;
    char busNo[10], source[20], destination[20], sourceTime[20], destinationTime[20];

public:
    // Constructor
    Bus();

    // Methods
    void _displayBusDetails();
    void addBus();
    void displayBuses();
    void displayBusDetailsByNo();
    void removeBus();
    void editBus();

    // Getters
    char *getBusNo()
    {
        return busNo;
    }

    char *getSource()
    {

        return source;
    }

    char *getDestination()
    {
        return destination;
    }

    char *getSourceTime()
    {
        return sourceTime;
    }

    char *getDestinationTime()
    {
        return destinationTime;
    }

    int getBookedSeats()
    {
        return bookedSeats;
    }

    int getMaxSeats()
    {
        return maxSeats;
    }

    double getBusFare()
    {
        return busFare;
    }

    // Setters
    void setBookedSeats()
    {
        bookedSeats++;
    }

    void setCancelTicket()
    {
        bookedSeats--;
    }

    void setSource(char *s)
    {
        if (s && s[0])
            strlcpy(source, s);
    }

    void setDestination(char *d)
    {
        if (d && d[0])
            strlcpy(destination, d);
    }

    void setSourceTime(char *s)
    {
        if (s && s[0])
            strlcpy(sourceTime, s);
    }

    void setDestinationTime(char *d)
    {
        if (d && d[0])
            strlcpy(destinationTime, d);
    }

    void setBusFare(double f)
    {
        if (f)
            busFare = f;
    }
};

#endif // BUS_H
