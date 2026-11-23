#include <iostream>
#include <string.h>

#include "Bus.cpp"
#include "Reservation.cpp"
#include "admin.h"
#include "utils.h"

using namespace std;

// Global Functions
void welcomeScreen();
void mainMenu();
void userMenu();
void adminLogin();
void adminMenu();
void reservationsMenu();

// `main` function or program entry point
int main()
{
    system("cls");
    system("COLOR 03");

    welcomeScreen();

    return 0;
}

//  Welcome screen function
void welcomeScreen()
{
    system("cls");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t||                  WELCOME TO                ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t||                                            ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t||      BUS RESERVATION SYSTEM MANAGEMENT     ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t||                                            ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t||                    PROJECT                 ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t================================================\n\n\n";

    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t  Developed By:-                             \t\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t                                             \t\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t  NIKHIL RAJPUT                              \t\n";
    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

    system("pause");
    mainMenu();
}

// Main menu function
void mainMenu()
{
    int choice;

    while (1)
    {
        system("cls");

        // Menu items
        printHeading("MAIN MENU");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. User Menu                                    \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. Admin Menu                                   \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. EXIT                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        if (!readNumber(choice))
            choice = 0;

        switch (choice)
        {
        case 1:
            userMenu();
            break;

        case 2:
            adminLogin();
            break;

        case 3:
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t\t  Thanks for using our project...!!! \t\t\t\n";
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t          Have a nice day...!!!      \t\t\t\n\n";
            exit(0);

        default:
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            break;
        }
    }
}

// User menu function
void userMenu()
{
    int choice;

    while (1)
    {
        system("cls");

        Reservation t;

        // Menu items
        printHeading("USER MENU");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. Book Ticket                                  \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. View Ticket                                  \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. Cancel Ticket                                \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 4. BACK                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        if (!readNumber(choice))
            choice = 0;

        switch (choice)
        {
        case 1:
            t.bookTicket();
            system("pause");
            break;

        case 2:
            t.viewReservationByPNR();
            system("pause");
            break;

        case 3:
            t.cancelReservation();
            system("pause");
            break;

        case 4:
            system("cls");
            return;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            break;
            userMenu();
        }
    }
}

// Admin login function
void adminLogin()
{
    string password, salt, hash;
    ifstream adminFileStream(ADMIN_FILE);

    system("cls");

    printHeading("ADMIN LOGIN");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!adminFileStream)
    {
        string confirm;

        cout << "\n\t\t\t\t\t\t\t\t\t\tNo admin password is set. Set one now (at least 8 characters).\n";
        cout << "\n\t\t\t\t\t\t\t\t\t\tNew Password:-> ";
        getline(cin, password);
        cout << "\n\t\t\t\t\t\t\t\t\t\tConfirm Password:-> ";
        getline(cin, confirm);

        if (!cin)
            exit(0);

        if (password.size() < 8 || password != confirm)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tPasswords must match and have at least 8 characters...!!! ";
            system("pause");
            return;
        }

        if (!saveAdminPassword(password))
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Save Changes...!!! ";
            system("pause");
            return;
        }

        adminMenu();
        return;
    }

    adminFileStream >> salt >> hash;

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Password:-> ";
    getline(cin, password);

    if (!cin)
        exit(0);

    if (salt.empty() || !sameHash(hashPassword(salt, password), hash))
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tWrong Password...!!! ";
        system("pause");
        return;
    }

    adminMenu();
}

// Admin menu function
void adminMenu()
{
    Bus b;
    Reservation r;

    int choice;

    while (1)
    {
        system("cls");

        printHeading("ADMIN PORTAL");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. Add Bus                                      \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. View Buses                                   \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. Book Ticket                                  \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 4. Edit Ticket                                  \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 5. Cancel Ticket                                \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 6. View Bookings                                \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 7. View Bus Details                             \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 8. Edit Bus                                     \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 9. Delete Bus                                   \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 10. BACK                                        \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        if (!readNumber(choice))
            choice = 0;

        switch (choice)
        {
        case 1:
            b.addBus();
            system("pause");
            break;

        case 2:
            b.displayBuses();
            system("pause");
            break;

        case 3:
            r.bookTicket();
            system("pause");
            break;

        case 4:
            r.editReservation();
            system("pause");
            break;

        case 5:
            r.cancelReservation();
            system("pause");
            break;

        case 6:
            reservationsMenu();
            break;

        case 7:
            b.displayBusDetailsByNo();
            system("pause");
            break;

        case 8:
            b.editBus();
            system("pause");
            break;

        case 9:
            b.removeBus();
            system("pause");
            break;

        case 10:
            system("cls");
            return;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            break;
        }
    }
}

// View reservations function
void reservationsMenu()
{
    Reservation t;

    int choice;

    while (1)
    {
        system("cls");

        printHeading("VIEW BOOKINGS");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. By PNR                                      \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. By Name                                      \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. By Bus                                       \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 4. By Source                                    \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 5. By Destination                               \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 6. All Bookings                                 \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 7. BACK                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        if (!readNumber(choice))
            choice = 0;

        switch (choice)
        {
        case 1:
            t.viewReservationByPNR();
            system("pause");
            break;

        case 2:
            t.viewReservationsByName();
            system("pause");
            break;

        case 3:
            t.viewReservationsByBusNo();
            system("pause");
            break;

        case 4:
            t.viewReservationsBySource();
            system("pause");
            break;

        case 5:
            t.viewReservationsByDestination();
            system("pause");
            break;

        case 6:
            t.viewReservations();
            system("pause");
            break;

        case 7:
            system("cls");
            return;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            break;
        }
    }
}
