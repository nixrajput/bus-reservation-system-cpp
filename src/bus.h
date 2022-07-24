#ifndef BUS_H
#define BUS_H

#include <iostream>

using namespace std;

// CLASS BUS
class Bus
{
private:
    int maxSeats, bookedSeats;
    double busFare;
    char busNo[10], source[20], destination[20], sourceTime[20], destinationTime[20];

public:
    Bus()
    {
        strcpy(busNo, "");
        maxSeats = 32;
        bookedSeats = 0;
        busFare = 0.0;
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(sourceTime, "");
        strcpy(destinationTime, "");
    }

    // METHODS
    void addBus();
    void showAllBus();
    void showBusDetails();
    void viewBusDetails();
    void deleteBus();
    void editBus();

    // GETTERS
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

    // SETTERS
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
            strcpy(source, s);
    }

    void setDestination(char *d)
    {
        if (d && d[0])
            strcpy(destination, d);
    }

    void setSourceTime(char *s)
    {
        if (s && s[0])
            strcpy(sourceTime, s);
    }

    void setDestinationTime(char *d)
    {
        if (d && d[0])
            strcpy(destinationTime, d);
    }

    void setBusFare(double f)
    {
        if (f)
            busFare = f;
    }
};
#endif // !BUS_H
