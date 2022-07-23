#include <iostream>
#include <string>
#include <cstring>

#include "ticket.h"
#include "bus.h"
#include "utils.h"

using namespace std;

// GENERATE TICKET
void Ticket::generateTicket(char *n, Bus b)
{
    strcpy(name, n);
    strcpy(pnrNo, generatePNR(99999).c_str());
    strcpy(date, getCurrentDate().c_str());
    bus = b;
}

// DISPLAY TICKET DETAILS
void Ticket::displayTicket()
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

// BOOK TICKET
void Ticket::bookTicket()
{
    system("cls");

    char from[20], to[20];
    int chk = 0;

    Bus b;
    fstream busFileStream, ticketFileStream, tempFileStream;

    printHeading("BOOK TICKET");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
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
            if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0)
            {
                b.showBusDetails();
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

            busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
            tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));
            while (!busFileStream.eof())
            {
                if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0 && strcmp(b.getBusNo(), bNo) == 0)
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
                        generateTicket(n, b);
                        ticketFileStream.open("tickets.dat", ios::out | ios::app | ios::binary);
                        ticketFileStream.write((char *)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        displayTicket();
                        cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!\n";
                    }
                }
                else
                {
                    tempFileStream.write((char *)&b, sizeof(b));
                }
                busFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                busFileStream.close();
                tempFileStream.close();
                remove("buses.dat");
                rename("temp.dat", "buses.dat");
            }
        }
        busFileStream.close();
    }
}

// CANCEL TICKET
void Ticket::cancelTicket()
{
    system("cls");

    char pnr[10];
    int chk = 0;

    Bus b;
    fstream busFileStream, ticketFileStream, tempFileStream;

    printHeading("CANCEL TICKET");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                //                busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
                //                busFileStream.read((char *)&b, sizeof(b));
                //                while (!busFileStream.eof())
                //                {
                //                    if (strcmp(b.getBusNo(), bus.getBusNo()) == 0)
                //                    {
                //                        b.setCancelTicket();
                //                    }
                //                    busFileStream.read((char *)&b, sizeof(b));
                //                }
                //                busFileStream.close();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            ticketFileStream.close();
            tempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }
        else
        {
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled...!!\n";
        }
    }
}

// EDIT TICKET
void Ticket::editTicket()
{
    system("cls");

    char pnr[10];
    int chk = 0;

    fstream ticketFileStream, tempFileStream;

    printHeading("EDIT TICKET");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                system("cls");
                printHeading("EDIT TICKET");

                displayTicket();
                char n[20];
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name :-> ";
                cin.getline(n, 20);
                setName(n);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk = 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }

        ticketFileStream.close();
        tempFileStream.close();
        remove("tickets.dat");
        rename("temp.dat", "tickets.dat");
    }
}

// SHOW TICKET BY NAME
void Ticket::showTicketsByName()
{
    system("cls");

    char n[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name:-> ";
    cin.ignore();
    cin.getline(n, 20);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmpi(getName(), n) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY BUS
void Ticket::showTicketsByBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
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
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY SOURCE
void Ticket::showTicketsBySource()
{
    system("cls");

    char s[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY SOURCE");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin.ignore();
    cin.getline(s, 20);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmpi(bus.getSource(), s) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY DESTINATION
void Ticket::showTicketsByDestination()
{
    system("cls");

    char d[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY DESTINATION");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.ignore();
    cin.getline(d, 20);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmpi(bus.getDestination(), d) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW ALL BOOKINGS
void Ticket::showAllTickets()
{
    system("cls");

    fstream ticketFileStream;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            displayTicket();
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        ticketFileStream.close();
    }
}
