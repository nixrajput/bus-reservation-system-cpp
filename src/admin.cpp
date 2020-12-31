#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <iomanip>

#include "admin.h"
#include "ticket.h"

using namespace std;

// ADD BUS FUNCTION
void Admin::addBus()
{
    fstream buses;

    system("cls");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ###################::ADD BUS::##################\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin >> busID;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Time:-> ";
    cin.ignore();
    cin.getline(Time, 50);
    cout << "\n\t\t\t\t\t\t\t\t\t\tDestination:-> ";
    cin.getline(DeptSt, 200);
    cout << "\n\t\t\t\t\t\t\t\t\t\tFare:-> ";
    cin >> fare;

    buses.open("buses.dat", ios::out | ios::app | ios::binary);
    buses.write((char *)this, sizeof(*this));
    buses.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// SHOW ALL BUS INFO FUNCTION
void Admin::showBus()
{

    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\tBus No:-> " << busID;
    cout << "\n\t\t\t\t\t\t\t\t\t\tDestination:-> " << DeptSt;
    cout << "\n\t\t\t\t\t\t\t\t\t\tTime:-> " << Time;
    cout << "\n\t\t\t\t\t\t\t\t\t\tSeats Remaining:-> " << max_seats - booked;
    cout << "\n\t\t\t\t\t\t\t\t\t\tFare:-> " << fare;
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";

    cout << "\n\n";
}

// VIEW BUS INFO FUNCTION
void Admin::viewBus()
{

    system("cls");

    fstream buses;

    buses.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!buses)
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        cout << "\n\n";
        cout << "\t                                                     ::BUS DETAILS::                                             \n\n";
        cout << "\t===================================================================================================================\n";
        cout << "\t"
             << "   Bus No." << setw(22) << "Destination" << setw(16) << "Arrival" << setw(20) << "Seats" << setw(16) << "Fare"
             << "\n";
        cout << "\t===================================================================================================================\n";

        buses.read((char *)this, sizeof(*this));

        while (!buses.eof())
        {
            cout << "\n\t    " << busID << setw(20) << DeptSt << setw(16) << Time << setw(22) << max_seats - booked << setw(18) << fare << "\n";
            buses.read((char *)this, sizeof(*this));
        }
        buses.close();
    }
}

//SHOW TICKET INFO FUNCTION
void Admin::showTicket()
{
    //cout<<"\n\t\t\t\tTicket No:-> " << ticketNo;
    cout << "\n\t\t\t\t\t\t\t\t\t\tBus No:-> " << busID;
    cout << "\n\t\t\t\t\t\t\t\t\t\tDestination:-> " << DeptSt;
    cout << "\n\t\t\t\t\t\t\t\t\t\tTime:-> " << Time;
    cout << "\n\t\t\t\t\t\t\t\t\t\tFare:-> " << fare;
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";

    cout << "\n\n";
}

// VIEW BOOKINGS FUNCTION
void Admin::viewBookings()
{
    Ticket t;
    fstream ticket;

    system("cls");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ################::YOUR BOOKINGS::###############\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        ticket.read((char *)&t, sizeof(t));
        while (!ticket.eof())
        {
            t.displayTicket();
            ticket.read((char *)&t, sizeof(t));
        }
    }

    ticket.close();
}

// CANCEL TICKET FUNCTION
void Admin::cancelTickets()
{
    system("cls");

    char cname[50];
    int chk = 0;
    Ticket t;
    fstream buses, ticket;

    cout << "\n\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Name:-> ";
    cin.ignore();
    cin.getline(cname, 50);

    ticket.open("tickets.dat", ios::in | ios::out | ios::app | ios::binary);
    buses.open("temp.dat", ios::out | ios::app | ios::binary);

    if (ticket.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        ticket.seekg(0, ios::beg);
        while (ticket.read((char *)&t, sizeof(t)))
        {
            if (strcmpi(t.getName(), cname) != 0)
            {
                buses.write((char *)&t, sizeof(t));
            }
            else
            {
                chk = 1;
            }
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled...!!";
        }
    }

    ticket.close();
    buses.close();
    remove("tickets.dat");
    rename("temp.dat", "tickets.dat");
}

// MODIFY TICKET FUNCTION
void Admin::modifyTickets()
{
    system("cls");

    char cname[50], name[50];
    int chk = 0;
    Ticket t;
    fstream ticket;

    cout << "\n\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Name:-> ";
    cin.ignore();
    cin.getline(cname, 50);

    ticket.open("tickets.dat", ios::in | ios::out | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        while (ticket.read((char *)&t, sizeof(t)))
        {
            if (strcmpi(t.getName(), cname) == 0)
            {
                t.displayTicket();
                ticket.seekg(0, ios::cur);
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tEnter New Details \n";
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                cin.getline(name, 50);
                ticket.seekp(ticket.tellg() - sizeof(t));
                ticket.write((char *)&t, sizeof(t));
                cout << "\n\t\t\t\t\t\t\t\t\t\tName Updated Successfully...!!";
                chk = 1;
            }
        }
        if (chk = 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tRecord Not Found...!!";
            system("pause");
        }
    }

    ticket.close();
}

// DELETE BUS FUNCTION
void Admin::deleteBus()
{
    system("cls");

    int bid;
    int chk = 0;
    Ticket t;
    Admin adm;
    fstream buses, ticket;

    cout << "\n\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin >> bid;

    buses.open("buses.dat", ios::in | ios::out | ios::app | ios::binary);
    ticket.open("temp.dat", ios::out | ios::app | ios::binary);

    if (buses.fail())
    {
        cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        buses.seekg(0, ios::beg);
        while (buses.read((char *)&adm, sizeof(Admin)))
        {
            if (adm.getBusId() != bid)
            {
                ticket.write((char *)&adm, sizeof(Admin));
            }
            else
            {
                chk = 1;
            }
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Deleted...!!";
        }
    }

    buses.close();
    ticket.close();
    remove("buses.dat");
    rename("temp.dat", "buses.dat");
}