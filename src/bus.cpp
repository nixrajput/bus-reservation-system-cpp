#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "bus.h"
#include "ticket.h"
#include "utils.h"

using namespace std;

// ADD BUS
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

    busFileStream.open("buses.dat", ios::out | ios::app | ios::binary);
    busFileStream.write((char *)this, sizeof(*this));
    busFileStream.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// SHOW BUS DETAILS
void Bus::showBusDetails()
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

// VIEW ALL BUS INFO
void Bus::showAllBus()
{
    system("cls");

    fstream busFileStream;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!busFileStream)
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        printHeading("BUSES");

        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            showBusDetails();
            busFileStream.read((char *)this, sizeof(*this));
        }
        busFileStream.close();
    }
}

// VIEW BUS INFO
void Bus::viewBusDetails()
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

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
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
                showBusDetails();
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

// EDIT BUS
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

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                system("cls");
                printHeading("EDIT BUS");

                showBusDetails();
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

        if (chk = 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

// DELETE BUS
void Bus::deleteBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream, tempFileStream;

    printHeading("DELETE BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);
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
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}
