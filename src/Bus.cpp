#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "Bus.h"
#include "Reservation.h"
#include "utils.h"

using namespace std;

// Initialie variables in constructor
Bus::Bus()
{
    strlcpy(busNo, "");
    maxSeats = 32;
    bookedSeats = 0;
    busFare = 0.0;
    strlcpy(source, "");
    strlcpy(destination, "");
    strlcpy(sourceTime, "");
    strlcpy(destinationTime, "");
}

// Display bus details
void Bus::_displayBusDetails()
{
    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t Bus No:-> " << getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Source:-> " << getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Destination:-> " << getDestination();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Time:-> " << getSourceTime() << " - " << getDestinationTime();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Total Seats:-> " << getMaxSeats();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Seats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << getBusFare();
    cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

// Add a bus
void Bus::addBus()
{
    fstream busFileStream;

    system("cls");

    printHeading("ADD BUS");

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(busNo, 10);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin.getline(source, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.getline(destination, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
    cin.getline(sourceTime, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
    cin.getline(destinationTime, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
    cin >> busFare;

    busFileStream.open("../data/buses.dat", ios::out | ios::app | ios::binary);
    busFileStream.write((char *)this, sizeof(*this));
    busFileStream.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// Display all buses
void Bus::displayBuses()
{
    system("cls");

    fstream busFileStream;

    busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);

    if (!busFileStream)
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        printHeading("BUSES");

        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            _displayBusDetails();
            busFileStream.read((char *)this, sizeof(*this));
        }

        busFileStream.close();
    }
}

// Display bus details by bus number
void Bus::displayBusDetailsByNo()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream;

    printHeading("VIEW BUS INFO");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");
    printHeading("BUS INFO");

    busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                _displayBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
    }
}

// Edit a bus details
void Bus::editBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;

    fstream busFileStream, tempFileStream;

    printHeading("EDIT BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        tempFileStream.open("../data/temp.dat", ios::out | ios::app | ios::binary);
        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                system("cls");
                printHeading("EDIT BUS");

                _displayBusDetails();
                char s[20], d[20], sTime[20], dTime[20];
                double fare;
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
                cin.getline(s, 20);
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
                cin.getline(d, 20);
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
                cin.getline(sTime, 20);
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
                cin.getline(dTime, 20);
                cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
                cin.ignore();
                cin >> fare;
                setSource(s);
                setDestination(d);
                setSourceTime(sTime);
                setDestinationTime(dTime);
                setBusFare(fare);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }

            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("../data/buses.dat");
        rename("../data/temp.dat", "../data/buses.dat");
    }
}

// Remove a bus
void Bus::removeBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream, tempFileStream;

    printHeading("DELETE BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    busFileStream.open("../data/buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }
    else
    {
        tempFileStream.open("../data/temp.dat", ios::out | ios::app | ios::binary);
        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Deleted...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("../data/buses.dat");
        rename("../data/temp.dat", "../data/buses.dat");
    }
}
