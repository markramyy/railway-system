// railway.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include "login.h"
#include "admin.h"
#include "Trains.h"
#include "trip.h"
#include "UserTripFunctions.h"

using namespace std;
void DELETEPOINTERS(map<string, Passenger*> passengers)
{
    for (auto it : passengers) {
        delete it.second;
}
}
int main()
{
    vector<Trip> tripsArray;
    getTripsVector(tripsArray);
    map<string, Passenger*> passengers;
    loadPassengerData(passengers);
    map<string, admin> admins;
    loadadminData(admins);


    int choice;
    do
    {

        cout << "1. Admin" << endl ;
        cout << "2. Passenger " << endl;
        cout << "3. Exit " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1 :
            do
            {

                cout << "1. Login\n";
                cout << "2. Quit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                        loginadmin(admins);
                        cout << "Press 1 to Add Train \nPress 2 to Delete Train \nPress 3 to Add Trip\nPress 4 to Modify Trip \nPress 5 to Delete Trip\n ";
                        cin >> choice;
                        if (choice == 1)
                        {
                            fillTrain();
                        }
                        else if (choice == 2)
                        {
                            displayTrains();
                            cout << endl;
                            deleteTrainFromVector();
                        }
                        else if (choice == 3)
                        {
                            AddTrip();
                        }
                        else if (choice == 4)
                        {
                            ModifyTrip();
                        }
                        else if (choice == 5)
                        {
                            DeleteTrip();
                        }
                        else
                        {
                            cout << "Invalid Choice !! " << endl;
                        }
                        break;
                    case 2:
                        saveadminData(admins);
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
            }while (choice != 2);
            break;
        case 2 :
                do {
                    cout << "1. Sign up\n";
                    cout << "2. Login\n";
                    cout << "3. Quit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        signUp(passengers);
                        break;
                    case 2:
                        login(passengers, tripsArray);
                        //passenger functions

                        break;
                    case 3:

                        savePassengerData(passengers);
                        updateTripsFile(tripsArray);
                        DELETEPOINTERS(passengers);
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
            } while (choice != 3);
            break;

        case 3:
            break;
        default:
            cout << "invalid Choice " << endl;
            break;
        }
    } while (choice != 3);

    return 0;

}

