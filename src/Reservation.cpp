#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "Reservation.h"
#include "Bus.h"
#include "utils.h"

using namespace std;

// Initialie variables in constructor
Reservation::Reservation() {}

// Generate a ticket
void Reservation::_generateTicket(char *n, Bus b)
{
    strlcpy(name, n);
    strlcpy(pnrNo, generatePNR(99999).c_str());
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

    busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);

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

            busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);
            busTempFileStream.open("../data/temp.dat", ios::out | ios::app | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));

            while (!busFileStream.eof())
            {
                if (strcmp(b.getSource(), from) == 0 && strcmp(b.getDestination(), to) == 0 && strcmp(b.getBusNo(), bNo) == 0)
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

                        reservationsFileStream.open("../data/reservations.dat", ios::out | ios::app | ios::binary);
                        reservationsFileStream.write((char *)this, sizeof(*this));
                        reservationsFileStream.close();
                        busTempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        _displayReservationDetails();
                        cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!\n";
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
                busTempFileStream.close();
                remove("../data/buses.dat");
                rename("../data/temp.dat", "../data/buses.dat");
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

    reservationsFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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

    char pnr[10];
    int chk = 0;

    fstream busFileStream, reservationsFileStream, reservationsTempFileStream, busTempFileStream;

    printHeading("CANCEL RESERVATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    reservationsFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);
    reservationsTempFileStream.open("../data/temp.dat", ios::out | ios::app | ios::binary);

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
                Bus b;
                busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);
                busTempFileStream.open("../data/bustemp.dat", ios::out | ios::app | ios::binary);

                busFileStream.read((char *)&b, sizeof(b));

                while (!busFileStream.eof())
                {
                    if (strcmp(b.getBusNo(), bus.getBusNo()) == 0)
                    {
                        b.setCancelTicket();
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    else
                    {
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }

                    busFileStream.read((char *)&b, sizeof(b));
                }
                busFileStream.close();
                busTempFileStream.close();
                remove("../data/buses.dat");
                rename("../data/bustemp.dat", "../data/buses.dat");
                chk = 1;
            }
            reservationsFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            reservationsFileStream.close();
            reservationsTempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Not Found...!!\n";
        }
        else
        {
            reservationsFileStream.close();
            reservationsTempFileStream.close();
            remove("../data/reservations.dat");
            rename("../data/temp.dat", "../data/reservations.dat");
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Cancelled...!!\n";
        }
    }
}

// Edit a reservation
void Reservation::editReservation()
{
    system("cls");

    char pnr[10];
    int chk = 0;

    fstream ticketFileStream, reservationsTempFileStream;

    printHeading("EDIT RESERVATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        reservationsTempFileStream.open("../data/temp.dat", ios::out | ios::app | ios::binary);

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

        if (chk == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tReservation Not Found...!!\n";
        }

        ticketFileStream.close();
        reservationsTempFileStream.close();
        remove("../data/reservations.dat");
        rename("../data/temp.dat", "../data/reservations.dat");
    }
}

// View reservation details by PNR number
void Reservation::viewReservationByPNR()
{
    system("cls");

    char pnr[10];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW RESERVATIONS BY PNR");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    system("cls");

    printHeading("RESERVATIONS");

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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

    ticketFileStream.open("../data/reservations.dat", ios::in | ios::app | ios::binary);

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
