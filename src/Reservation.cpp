#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>

#include "Reservation.h"
#include "Bus.h"
#include "utils.h"

using namespace std;

// Initialie variables in constructor
Reservation::Reservation() {}

// True if a saved ticket already uses this PNR
static bool pnrExists(const char *pnr)
{
    ifstream reservationsFileStream("../data/reservations.dat", ios::in | ios::binary);
    Reservation r;

    while (reservationsFileStream.read((char *)&r, sizeof(r)))
    {
        if (strcmp(r.getPnrNo(), pnr) == 0)
            return true;
    }
    return false;
}

// Generate a ticket
void Reservation::_generateTicket(char *n, Bus b)
{
    strlcpy(name, n);
    do
        strlcpy(pnrNo, generatePNR().c_str());
    while (pnrExists(pnrNo));
    strlcpy(date, getCurrentDate().c_str());
    bus = b;
}

// Display the reservation details
void Reservation::_displayReservationDetails()
{
    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t Name:-> " << getName();
    cout << "\n\t\t\t\t\t\t\t\t\t\t PNR No:-> " << getPnrNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus No:-> " << bus.getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Seat No.:-> " << bus.getBookedSeats();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Date:-> " << getDate();
    cout << "\n\t\t\t\t\t\t\t\t\t\t From:-> " << bus.getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t To:-> " << bus.getDestination();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Source Time:-> " << bus.getSourceTime();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Destination Time:-> " << bus.getDestinationTime();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << bus.getBusFare();
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

// Book a ticket
void Reservation::bookTicket()
{
    system("cls");

    char from[20], to[20];
    int chk = 0;

    Bus b;
    fstream busFileStream, reservationsFileStream, busTempFileStream;

    printHeading("BOOK TICKET");

    busFileStream.open("../data/buses.dat", ios::in | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
        cin.ignore();
        cin.getline(from, 20);
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
        cin.getline(to, 20);

        system("cls");
        printHeading("AVAILABLE BUSES");

        busFileStream.read((char *)&b, sizeof(b));

        while (!busFileStream.eof())
        {
            if (strcmp(b.getSource(), from) == 0 && strcmp(b.getDestination(), to) == 0)
            {
                b._displayBusDetails();
                chk = 1;
            }

            busFileStream.read((char *)&b, sizeof(b));
        }

        busFileStream.close();

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Buses Found...!!\n";
        }
        else
        {
            char bNo[10];
            int booked = 0;

            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
            cin.getline(bNo, 10);

            busFileStream.open("../data/buses.dat", ios::in | ios::binary);
            busTempFileStream.open("../data/temp.dat", ios::out | ios::trunc | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));

            while (!busFileStream.eof())
            {
                if (booked == 0 && strcmp(b.getSource(), from) == 0 && strcmp(b.getDestination(), to) == 0 && strcmp(b.getBusNo(), bNo) == 0)
                {
                    if (b.getBookedSeats() >= 32)
                    {
                        cout << "\n\t\t\t\t\t\t\t\t\t\tSeat not available...!!\n";
                        break;
                    }
                    else
                    {
                        system("cls");
                        printHeading("BOOK TICKET");
                        char n[20];
                        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                        cin.getline(n, 20);
                        b.setBookedSeats();
                        _generateTicket(n, b);
                        busTempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                    }
                }
                else
                {
                    busTempFileStream.write((char *)&b, sizeof(b));
                }

                busFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                busFileStream.close();

                // Save the seat first: if the ticket write then fails, the bus is short a seat, never overbooked.
                bool saved = replaceDataFile(busTempFileStream, "../data/temp.dat", "../data/buses.dat");
                if (saved)
                {
                    reservationsFileStream.open("../data/reservations.dat", ios::out | ios::app | ios::binary);
                    reservationsFileStream.write((char *)this, sizeof(*this));
                    reservationsFileStream.close();
                    saved = !reservationsFileStream.fail();
                }

                if (!saved)
                {
                    cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Save Changes...!!\n";
                }
                else
                {
                    system("cls");
                    printHeading("BOOKING DETAILS");
                    _displayReservationDetails();
                    cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!\n";
                }
            }
        }

        busFileStream.close();
    }
}

// View all reservations
void Reservation::viewReservations()
{
    system("cls");

    fstream reservationsFileStream;

    system("cls");

    printHeading("RESERVATIONS");

    reservationsFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (reservationsFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        reservationsFileStream.read((char *)this, sizeof(*this));

        while (!reservationsFileStream.eof())
        {
            _displayReservationDetails();
            reservationsFileStream.read((char *)this, sizeof(*this));
        }

        reservationsFileStream.close();
    }
}

// Cancel a reservation
void Reservation::cancelReservation()
{
    system("cls");

    char pnr[11];
    vector<string> cancelledBusNos;

    fstream busFileStream, reservationsFileStream, reservationsTempFileStream, busTempFileStream;

    printHeading("CANCEL RESERVATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 11);

    reservationsFileStream.open("../data/reservations.dat", ios::in | ios::binary);
    reservationsTempFileStream.open("../data/temp.dat", ios::out | ios::trunc | ios::binary);

    if (reservationsFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        reservationsFileStream.read((char *)this, sizeof(*this));

        while (!reservationsFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) != 0)
            {
                reservationsTempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                cancelledBusNos.push_back(bus.getBusNo());
            }
            reservationsFileStream.read((char *)this, sizeof(*this));
        }
        reservationsFileStream.close();

        if (cancelledBusNos.empty())
        {
            reservationsTempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Not Found...!!\n";
        }
        // Remove the ticket first: if the seat update then fails, the bus is short a seat, never overbooked.
        else if (!replaceDataFile(reservationsTempFileStream, "../data/temp.dat", "../data/reservations.dat"))
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Save Changes...!!\n";
        }
        else
        {
            Bus b;
            busFileStream.open("../data/buses.dat", ios::in | ios::binary);
            busTempFileStream.open("../data/bustemp.dat", ios::out | ios::trunc | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));

            while (!busFileStream.eof())
            {
                for (size_t i = 0; i < cancelledBusNos.size(); i++)
                {
                    if (cancelledBusNos[i] == b.getBusNo())
                        b.setCancelTicket();
                }
                busTempFileStream.write((char *)&b, sizeof(b));
                busFileStream.read((char *)&b, sizeof(b));
            }

            bool busesRead = busFileStream.is_open();
            busFileStream.close();

            if (busesRead && replaceDataFile(busTempFileStream, "../data/bustemp.dat", "../data/buses.dat"))
            {
                cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Cancelled...!!\n";
            }
            else
            {
                cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Cancelled, but the seat count was not updated...!!\n";
            }
        }
    }
}

// Edit a reservation
void Reservation::editReservation()
{
    system("cls");

    char pnr[11];
    int chk = 0;

    fstream ticketFileStream, reservationsTempFileStream;

    printHeading("EDIT RESERVATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 11);

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        reservationsTempFileStream.open("../data/temp.dat", ios::out | ios::trunc | ios::binary);

        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                system("cls");
                printHeading("EDIT RESERVATION");

                _displayReservationDetails();
                char n[20];
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name :-> ";
                cin.getline(n, 20);
                setName(n);
                reservationsTempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                reservationsTempFileStream.write((char *)this, sizeof(*this));
            }

            ticketFileStream.read((char *)this, sizeof(*this));
        }

        ticketFileStream.close();

        if (!replaceDataFile(reservationsTempFileStream, "../data/temp.dat", "../data/reservations.dat"))
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Save Changes...!!\n";
        }
        else if (chk == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Not Found...!!\n";
        }
    }
}

// View reservation details by PNR number
void Reservation::viewReservationByPNR()
{
    system("cls");

    char pnr[11];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY PNR");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 11);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                _displayReservationDetails();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Reservations...!!\n";
        }

        ticketFileStream.close();
    }
}

// View reservations by a passenger name
void Reservation::viewReservationsByName()
{
    system("cls");

    char n[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name:-> ";
    cin.ignore();
    cin.getline(n, 20);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(getName(), n) == 0)
            {
                _displayReservationDetails();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Reservations...!!\n";
        }

        ticketFileStream.close();
    }
}

// View reservations by a bus number
void Reservation::viewReservationsByBusNo()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(bus.getBusNo(), bNo) == 0)
            {
                _displayReservationDetails();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Reservations...!!\n";
        }

        ticketFileStream.close();
    }
}

// View reservations by the source station
void Reservation::viewReservationsBySource()
{
    system("cls");

    char s[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY SOURCE");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin.ignore();
    cin.getline(s, 20);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(bus.getSource(), s) == 0)
            {
                _displayReservationDetails();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Reservations...!!\n";
        }

        ticketFileStream.close();
    }
}

// View reservations by the destination station
void Reservation::viewReservationsByDestination()
{
    system("cls");

    char d[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY DESTINATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.ignore();
    cin.getline(d, 20);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));

        while (!ticketFileStream.eof())
        {
            if (strcmp(bus.getDestination(), d) == 0)
            {
                _displayReservationDetails();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Reservation...!!\n";
        }

        ticketFileStream.close();
    }
}
