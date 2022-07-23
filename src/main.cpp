#include <iostream>
#include <string.h>

#include "bus.cpp"
#include "ticket.cpp"
#include "utils.h"
// #include "customer.h"

using namespace std;

// GLOBAL FUNCTION
void mainMenu();
void userMenu();
void adminMenu();
void adminLogin();
void viewBookingsMenu();
void welcomeScreen();

// MAIN FUNCTION
int main()
{
    system("cls");
    system("COLOR 0f");

    //    string root_pass = "";
    //    char ch;
    //    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    //    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    //    cout << "\t\t\t\t\t\t\t\t\t\tEnter Master Password:-> ";
    //    ch = _getch();
    //    while (ch != 13) // Max 13 characters
    //    {
    //        root_pass.push_back(ch);
    //        ch = _getch();
    //        cout << "*";
    //    }
    //    if (root_pass == "123")
    //    {
    //        welcomeScreen();
    //    }
    //    else
    //    {
    //        system("cls");
    //        cout << "\n\n\n\n\n\n\n";
    //        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\tAccess Denied...!!!\n\n";
    //        system("pause");
    //        main();
    //    }

    welcomeScreen();

    return 0;
}

//  WELCOME SCREEN FUNCTION
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

// MAIN MENU FUNCTION
void mainMenu()
{
    int choice;

    while (1)
    {
        system("cls");

        // MENU ITEMS
        printHeading("MAIN MENU");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. User Menu                                    \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. Admin Menu                                   \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. EXIT                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> choice;

        switch (choice)

        {

        case 1:
            userMenu();
            break;

        case 2:
            adminMenu();
            break;

        case 3:
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t\t  Thanks for using our project...!!! \t\t\t\n";
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t          Have a nice day...!!!      \t\t\t\n\n";
            exit(0);

        default:
            cout << "\n\n\t\t\t\t\t\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            mainMenu();
        }
    }
}

// USER MENU FUNCTION
void userMenu()
{

    int usr_choice;

    while (1)
    {
        system("cls");

        // MENU ITEMS
        printHeading("USER MENU");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. Book Ticket                                  \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. View Bookings                                \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. Cancel Ticket                                \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 4. BACK                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> usr_choice;

        switch (usr_choice)

        {

            //        case 1:
            //            cust1.bookTicket();
            //            break;
            //
            //        case 2:
            //            cust1.viewBookings();
            //            system("pause");
            //            break;
            //
            //        case 3:
            //            cust1.cancelTicket();
            //            system("pause");
            //            break;
            //
        case 4:
            system("cls");
            mainMenu();
            break;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            break;
            userMenu();
        }
    }
}

// ADMIN MENU FUNCTION
void adminMenu()
{
    Bus b;
    Ticket t;

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

        cin >> choice;

        switch (choice)

        {

        case 1:
            b.addBus();
            system("pause");
            break;

        case 2:
            b.showAllBus();
            system("pause");
            break;

        case 3:
            t.bookTicket();
            system("pause");
            break;

        case 4:
            t.editTicket();
            system("pause");
            break;

        case 5:
            t.cancelTicket();
            system("pause");
            break;

        case 6:
            viewBookingsMenu();
            break;

        case 7:
            b.viewBusDetails();
            system("pause");
            break;

        case 8:
            b.editBus();
            system("pause");
            break;

        case 9:
            b.deleteBus();
            system("pause");
            break;

        case 10:
            system("cls");
            mainMenu();
            break;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            adminMenu();
        }
    }
}

// VIEW BOOKINGS MENU FUNCTION
void viewBookingsMenu()
{
    Ticket t;

    int choice;

    while (1)
    {
        system("cls");

        printHeading("VIEW BOOKINGS");

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 1. By Name                                      \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 2. By Bus                                       \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 3. By Source                                    \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 4. By Destination                               \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 5. All Bookings                                 \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t 6. BACK                                         \n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> choice;

        switch (choice)

        {

        case 1:
            t.showTicketsByName();
            system("pause");
            break;

        case 2:
            t.showTicketsByBus();
            system("pause");
            break;

        case 3:
            t.showTicketsBySource();
            system("pause");
            break;

        case 4:
            t.showTicketsByDestination();
            system("pause");
            break;

        case 5:
            t.showAllTickets();
            system("pause");
            break;

        case 6:
            system("cls");
            adminMenu();
            break;

        default:
            cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
            system("pause");
            viewBookingsMenu();
        }
    }
}

// // ADMIN LOGIN FUNCTION
// void adminLogin()
// {
//     string adminUname, adminPass;

//     system("cls");

//     cout << "\n\n\n\n";
//     cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
//     cout << "\t\t\t\t\t\t\t\t\t\t #################::ADMIN LOGIN::################\n";
//     cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

//     cout << "\n\t\t\t\t\t\t\t\t\t\tEnter AdminID:-> ";
//     cin >> adminUname;
//     cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Password:-> ";
//     cin >> adminPass;

//     if (adminUname == "admin" && adminPass == "pass")
//     {
//         adminMenu();
//     }
//     else
//     {
//         cout << "\n\t\t\t\t\t\t\t\t\t\tUsername or Password is wrong...!!! ";
//         system("pause");
//         adminLogin();
//     }
// }
