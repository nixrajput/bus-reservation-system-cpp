#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <iomanip>

#include "customer.h"
#include "ticket.h"
#include "admin.h"

using namespace std;

// CUSTOMER BOOK TICKET FUNCTION
void Customer::bookTicket()
{
    system("cls");

    char from[200], name[50];
    int chk = 0;

    Ticket t;
    Admin ad;
    fstream buses, ticket;

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ###############::TICKET BOOKING::###############\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.ignore();
    cin.getline(from, 200);

    buses.open("buses.dat", ios::in | ios::out | ios::app | ios::binary);
    if (buses.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        while (buses.read((char *)&ad, sizeof(ad)))
        {
            if (strcmpi(ad.getDeptSt(), from) == 0)
            {
                system("cls");
                cout << "\n\n\n\n";
                cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
                cout << "\t\t\t\t\t\t\t\t\t\t ###############::AVAILABLE BUSES::##############\n";
                cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";
                ad.showBus();
                chk = 1;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                cin.getline(name, 50);
                ad.book();
                //ad.setTicketNo();
                t.generateTicket(name, ad);
                ticket.open("tickets.dat", ios::out | ios::app | ios::binary);
                ticket.write((char *)&t, sizeof(t));
                ticket.close();

                buses.seekp(buses.tellg() - sizeof(ad), ios::beg);
                buses.write((char *)&ad, sizeof(ad));

                cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!";
                //cout << "\n\t\t\t\t\t\t\t\t\t\tYour Alloted TicketNo is [" << ad.getTicketNo() << "]";
                //cout << "\n\t\t\t\t\t\t\t\t\t\tPlease Remember Your TicketNo Carefully...!!";
            }
        }

        if (chk == 0)
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Buses Found...!!";
        system("pause");
    }

    buses.close();
}

// CUSTOMER VIEW BOOKINGS FUNCTION
void Customer::viewBookings()
{
    system("cls");

    char cname[50];
    int chk = 0;
    Ticket t;
    fstream ticket;

    cout << "\n\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Name:-> ";
    cin.ignore();
    cin.getline(cname, 50);

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
        while (ticket.read((char *)&t, sizeof(t)))
        {
            if (strcmpi(t.getName(), cname) == 0)
            {
                t.displayTicket();
                chk = 1;
            }
        }
        if (chk = 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!";
            system("pause");
        }
    }

    ticket.close();
}

void Customer::cancelTicket()
{
    system("cls");

    char cname[50];
    int chk = 0;
    Ticket t;
    Admin ad;
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