#include <iostream>
#include <conio.h>

#include "admin.h"
#include "customer.h"

using namespace std;

// GLOBAL FUNCTION
void mainMenu();
void userMenu();
void adminMenu();
void welcomeScreen();

// MAIN FUNCTION
int main()
{
    system("cls");
    system("COLOR 0f");

    string root_pass = "";
    char ch;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\tEnter Master Password:-> ";
    ch = _getch();
    while (ch != 13) // Max 13 characters
    {
        root_pass.push_back(ch);
        ch = _getch();
        cout << "*";
    }
    if (root_pass == "123")
    {
        welcomeScreen();
    }
    else
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n";
        cout << "\n\n\n\t\t\t\t\t\t\t\t\t\tAccess Denied...!!!\n\n";
        system("pause");
        main();
    }

    return 0;
}

// ADMIN LOGIN FUNCTION
void adminLogin()
{
    string adminUname, adminPass;

    system("cls");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t #################::ADMIN LOGIN::################\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter AdminID:-> ";
    cin >> adminUname;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Password:-> ";
    cin >> adminPass;

    if (adminUname == "admin" && adminPass == "pass")
    {
        adminMenu();
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tUsername or Password is wrong...!!! ";
        system("pause");
        adminLogin();
    }
}

//  WELCOME SCREEN FUNCTION
void welcomeScreen()
{
    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ||                  WELCOME TO                ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ||            BUS RESERVATION SYSTEM          ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ||                    PROJECT                 ||\n";
    cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

    cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t  Developed By:-           \t\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t                           \t\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t  NIKHIL KUMAR             \t\n";
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
        cout << "\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t\t #################::MAIN MENU::##################\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t1. Customer Portal \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t2. Admin Portal \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t3. EXIT \t\t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> choice;

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
            mainMenu();
        }
    }
}

// USER MENU FUNCTION
void userMenu()
{
    Customer cust1;

    int usr_choice;

    while (1)
    {
        system("cls");

        // MENU ITEMS
        cout << "\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t\t #################::USER PORTAL::################\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t1. Book Ticket       \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t2. View Bookings     \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t3. Cancel Ticket     \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t4. BACK              \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> usr_choice;

        switch (usr_choice)

        {

        case 1:
            cust1.bookTicket();
            break;

        case 2:
            cust1.viewBookings();
            system("pause");
            break;

        case 3:
            cust1.cancelTicket();
            system("pause");
            break;

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
    Admin adm1;

    int admn_choice;

    while (1)
    {
        system("cls");

        // MENU ITEMS
        cout << "\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ################::ADMIN PORTAL::################\n";
        cout << "\t\t\t\t\t\t\t\t\t\t ================================================\n\n\n";

        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t1. Add Bus            \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t2. View Buses         \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t3. View Bookings      \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t4. Cancel Ticket      \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t5. Modify Booking     \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t6. Delete Bus         \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t|\t7. BACK               \t\t\t|\n";
        cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

        cin >> admn_choice;

        switch (admn_choice)

        {

        case 1:
            adm1.addBus();
            system("pause");
            break;

        case 2:
            adm1.viewBus();
            cout << "\n\n";
            system("pause");
            break;

        case 3:
            adm1.viewBookings();
            system("pause");
            break;

        case 4:
            adm1.cancelTickets();
            system("pause");
            break;

        case 5:
            adm1.modifyTickets();
            break;

        case 6:
            adm1.deleteBus();
            break;

        case 7:
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
